#include "SRuntimeViewportDetails.h"

#include "PropertySlates/SRuntimeArrayProperty.h"
#include "PropertySlates/SRuntimeBoolProperty.h"
#include "PropertySlates/SRuntimeFloatProperty.h"
#include "PropertySlates/SRuntimeIntProperty.h"
#include "PropertySlates/SRuntimeRotatorProperty.h"
#include "PropertySlates/SRuntimeStringProperty.h"
#include "PropertySlates/SRuntimeStructProperty.h"
#include "PropertySlates/SRuntimeVectorProperty.h"

TMap<FString, TFunction<TSharedPtr<SRuntimePropertySlateBase>()>> SRuntimeViewportDetails::RuntimePropertyCreators
{
	{"int32", []() { return SNew(SRuntimeIntProperty); }},
	{"FString", []() { return SNew(SRuntimeStringProperty); }},
	{"float", []() { return SNew(SRuntimeFloatProperty); }},
	{"bool", []() { return SNew(SRuntimeBoolProperty); }},
	{"FVector", []() { return SNew(SRuntimeVectorProperty); }},
	{"FRotator", []() { return SNew(SRuntimeRotatorProperty); }},
	{"TArray", []() { return SNew(SRuntimeArrayProperty); }},
};

void SRuntimeViewportDetails::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SAssignNew(Overlay, SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SEditableTextBox)
				.Text_Lambda([this]()
				{
					if (BaseClass.IsValid())
					{
						return FText::FromString(BaseClass->GetName());
					}
					if (Struct.IsValid())
					{
						return FText::FromString(Struct->GetName());
					}

					return FText::FromString("Null Ptr");
				})
				.IsReadOnly(true)
				.Visibility_Lambda([this]()
				{
					return DisplayName ? EVisibility::Visible : EVisibility::Collapsed;
				})
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SAssignNew(WrapBox, SWrapBox)
				.Orientation(Orient_Horizontal)
				.UseAllottedSize(true)
			]
		]
	];
}

void SRuntimeViewportDetails::SetRuntimePropertySlate(
	const TArray<TSharedPtr<SRuntimePropertySlateBase>>& CompoundWidgets) const
{
	WrapBox->ClearChildren();

	for (const TSharedPtr<SRuntimePropertySlateBase>& Widget : CompoundWidgets)
	{
		FProperty* Property = Widget->Property;
		FString String = Property->GetName();

		// Property name
		WrapBox->AddSlot()
		       .ForceNewLine(true)
		[
			SNew(SBox)
			.WidthOverride_Lambda([this]() { return NameWidth; })
			[
				SNew(SEditableTextBox)
				.Text(FText::FromString(String))
				.IsReadOnly(true)
			]
		];

		// Property value
		WrapBox->AddSlot()
		       .FillEmptySpace(true)
		[
			Widget.ToSharedRef()
		];
	}
}

void SRuntimeViewportDetails::SetObjects(const TArray<UObject*>& InObjects)
{
	for (UObject* Object : InObjects)
	{
		Objects.Add(Object);
	}

	if (Objects.Num() > 0 && Objects[0].IsValid())
	{
		BaseClass = Objects[0]->GetClass();
	}
	else
	{
		BaseClass = nullptr;
	}

	if (BaseClass.IsValid())
	{
		const TArray<TSharedPtr<SRuntimePropertySlateBase>>& CompoundWidgets
			= GetPropertySlates(BaseClass.Get(), Objects[0].Get());

		SetRuntimePropertySlate(CompoundWidgets);
	}
}

void SRuntimeViewportDetails::SetStruct(const TObjectPtr<UScriptStruct>& InStruct)
{
	Struct = InStruct;

	TArray<TSharedPtr<SRuntimePropertySlateBase>> StructWidgets;
	for (TFieldIterator<FProperty> StructIt(InStruct); StructIt; ++StructIt)
	{
		if (!StructIt->HasMetaData("Debugger"))
			continue;
		
		GetPropertySlates(InStruct, *StructIt, StructWidgets);
	}

	SetRuntimePropertySlate(StructWidgets);
}

void SRuntimeViewportDetails::SetProperty(FProperty* InProperty, void* InRaw)
{
	TArray<TSharedPtr<SRuntimePropertySlateBase>> CompoundWidgets;
	GetPropertySlates(InRaw, InProperty, CompoundWidgets);
	SetRuntimePropertySlate(CompoundWidgets);
	DisplayName = false;
}

TArray<AActor*> SRuntimeViewportDetails::GetActors() const
{
	TArray<AActor*> Actors;
	for (TWeakObjectPtr<UObject> Object : Objects)
	{
		if (AActor* Actor = Cast<AActor>(Object))
		{
			Actors.Add(Actor);
		}
	}
	return Actors;
}

TArray<UObject*> SRuntimeViewportDetails::GetObjects() const
{
	TArray<UObject*> Result;
	for (TWeakObjectPtr<UObject> Object : Objects)
	{
		if (UObject* Obj = Object.Get())
		{
			Result.Add(Obj);
		}
	}
	return Result;
}

void SRuntimeViewportDetails::GetPropertySlates(void* InObject, FProperty* It,
                                                TArray<TSharedPtr<SRuntimePropertySlateBase>>& CompoundWidgets)
{
	const FString& CPPType = It->GetCPPType();
	
	TFunction<TSharedPtr<SRuntimePropertySlateBase>()>* Creator = RuntimePropertyCreators.Find(CPPType);
	if (!Creator)
	{
		if (It->IsA(FStructProperty::StaticClass()))
		{
			TSharedPtr<SRuntimeStructProperty> RuntimeStructProperty = SNew(SRuntimeStructProperty);
			FStructProperty* StructProperty = CastField<FStructProperty>(It);
			TObjectPtr<UScriptStruct> ScriptStruct = StructProperty->Struct;
			RuntimeStructProperty->SetStruct(ScriptStruct);
			RuntimeStructProperty->SetProperty(It, InObject);
			CompoundWidgets.Add(RuntimeStructProperty);
			return;
		}
		if (It->IsA(FObjectPropertyBase::StaticClass()))
		{
			FObjectProperty* ObjectProperty = CastField<FObjectProperty>(It);
			UObject* ObjectPropertyValue = ObjectProperty->GetObjectPropertyValue(
				ObjectProperty->ContainerPtrToValuePtr<UObject>(InObject));

			TSharedPtr<SRuntimeStructProperty> RuntimeStructProperty = SNew(SRuntimeStructProperty);
			RuntimeStructProperty->SetObjects({ObjectPropertyValue});
			RuntimeStructProperty->SetProperty(It, InObject);
			CompoundWidgets.Add(RuntimeStructProperty);
			return;
		}

		UE_LOG(LogTemp, Warning, TEXT("No property slate found for type: %s"), *CPPType);
		return;
	}

	TSharedPtr<SRuntimePropertySlateBase> Slate = Creator->operator()();
	Slate->SetProperty(It, InObject);
	CompoundWidgets.Add(Slate);
}

bool SRuntimeViewportDetails::HasPropertyCreator(const FProperty* It)
{
	return RuntimePropertyCreators.Contains(It->GetCPPType());
}

TArray<TSharedPtr<SRuntimePropertySlateBase>> SRuntimeViewportDetails::GetPropertySlates(
	const UClass* InClass, UObject* InObject)
{
	TArray<TSharedPtr<SRuntimePropertySlateBase>> PropertySlates;

	for (TFieldIterator<FProperty> It(InClass); It; ++It)
	{
		if (!It->HasMetaData("Debugger"))
			continue;
		
		GetPropertySlates(InObject, *It, PropertySlates);
	}

	return PropertySlates;
}
