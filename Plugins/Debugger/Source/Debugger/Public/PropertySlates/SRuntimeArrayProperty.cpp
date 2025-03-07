#include "SRuntimeArrayProperty.h"

void SRuntimeArrayProperty::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(200.0f)
		.HeightOverride(200.0f)
		[
			SAssignNew(ScrollBox, SScrollBox)
			.Orientation(Orient_Vertical)
			.ScrollBarAlwaysVisible(false)
		]
	];
}

void SRuntimeArrayProperty::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SRuntimePropertySlateBase::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	void* ArrayPtr = ArrayProperty->ContainerPtrToValuePtr<void>(Object);
	FScriptArrayHelper ArrayHelper(ArrayProperty, ArrayPtr);
	int32 Num = ArrayHelper.Num();

	for (int32 i = 0; i < Num; ++i)
	{
		FProperty* ItemProperty = ArrayProperty->Inner;

		TSharedPtr<SRuntimeViewportDetails> PropertySlate = nullptr;
		if (PropertySlates.IsValidIndex(i))
		{
			PropertySlate = PropertySlates[i];
		}
		else
		{
			PropertySlate = SNew(SRuntimeViewportDetails);
			PropertySlates.Add(PropertySlate);

			ScrollBox->AddSlot()
			[
				PropertySlate.ToSharedRef()
			];
		}

		uint8* Ptr = ArrayHelper.GetRawPtr(i);

		if (SRuntimeViewportDetails::HasPropertyCreator(ItemProperty))
		{
			PropertySlate->SetProperty(ItemProperty, Ptr);
			continue;
		}

		if (ItemProperty->IsA(FObjectProperty::StaticClass()))
		{
			UObject** RawPtr = reinterpret_cast<UObject**>(Ptr);
			PropertySlate->SetObjects({*RawPtr});
			continue;
		}
		if (ItemProperty->IsA(FStructProperty::StaticClass()))
		{
			FStructProperty* StructProperty = CastField<FStructProperty>(ItemProperty);
			TObjectPtr<UScriptStruct> ScriptStruct = StructProperty->Struct;
			PropertySlate->SetStruct(ScriptStruct);
			continue;
		}

		PropertySlate->SetProperty(ItemProperty, Ptr);
	}
}

void SRuntimeArrayProperty::SetProperty(FProperty* InProperty, void* InObject)
{
	SRuntimePropertySlateBase::SetProperty(InProperty, InObject);

	ArrayProperty = CastField<FArrayProperty>(InProperty);
}
