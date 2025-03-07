#include "SRuntimeViewportDetails.h"

#include "PropertySlates/SRuntimeIntProperty.h"
#include "PropertySlates/SRuntimeStringProperty.h"

TMap<FString, TFunction<TSharedPtr<SRuntimePropertySlateBase>()>> SRuntimeViewportDetails::RuntimePropertyCreators
{
	{"int32", []() { return SNew(SRuntimeIntProperty); }},
	{"FString", []() { return SNew(SRuntimeStringProperty); }},
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
			SAssignNew(WrapBox, SWrapBox)
			.Orientation(Orient_Horizontal)
		]
	];
}

void SRuntimeViewportDetails::SetObjects(const TArray<UObject*>& InObjects)
{
	for (UObject* Object : InObjects)
	{
		Objects.Add(Object);
	}

	if (Objects.Num() > 0)
	{
		BaseClass = Objects[0]->GetClass();
	}
	else
	{
		BaseClass = nullptr;
	}

	const TArray<TSharedPtr<SRuntimePropertySlateBase>>& CompoundWidgets
		= GetPropertySlates(BaseClass.Get(), Objects[0].Get());

	WrapBox->ClearChildren();
	
	for (const TSharedPtr<SRuntimePropertySlateBase>& Widget : CompoundWidgets)
	{
		FProperty* Property = Widget->Property;
		FString String = Property->GetName();

		// Property name
		WrapBox->AddSlot()
		[
			SNew(SEditableTextBox)
			.Text(FText::FromString(String))
			.IsReadOnly(true)
		];

		// Property value
		WrapBox->AddSlot()
		[
			Widget.ToSharedRef()
		];
	}
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

TArray<TSharedPtr<SRuntimePropertySlateBase>> SRuntimeViewportDetails::GetPropertySlates(
	const UClass* InClass, UObject* InObject)
{
	TArray<TSharedPtr<SRuntimePropertySlateBase>> PropertySlates;

	for (TFieldIterator<FProperty> It(InClass); It; ++It)
	{
		const FString& CPPType = It->GetCPPType();
		if (!It->HasMetaData("Debugger"))
			continue;

		TFunction<TSharedPtr<SRuntimePropertySlateBase>()>* Creator = RuntimePropertyCreators.Find(CPPType);
		if (!Creator)
			continue;

		TSharedPtr<SRuntimePropertySlateBase> Slate = Creator->operator()();
		Slate->SetProperty(*It, InObject);
		PropertySlates.Add(Slate);
	}

	return PropertySlates;
}
