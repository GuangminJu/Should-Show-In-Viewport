
#include "SRuntimeBoolProperty.h"

void SRuntimeBoolProperty::Construct(const FArguments& InArgs)
{
	TSRuntimePropertySlateBase<bool>::Construct(InArgs);

	ChildSlot
	[
		SNew(SBorder)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SCheckBox)
			.HAlign(HAlign_Center)
			.OnCheckStateChanged_Lambda(
				[this](ECheckBoxState InState)
				{
					SetValue(InState == ECheckBoxState::Checked);
				})
			.IsChecked_Lambda(
				[this]() -> ECheckBoxState
				{
					return GetValue() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
				})
		]
		];
}

void SRuntimeBoolProperty::SetProperty(FProperty* InProperty, void* InObject)
{
	TSRuntimePropertySlateBase<bool>::SetProperty(InProperty, InObject);

	Set.BindLambda(
		[this](bool InValue)
		{
			if (bool* ContainerPtrToValuePtr = Property->ContainerPtrToValuePtr<bool>(Object ))
			{
				*ContainerPtrToValuePtr = InValue;
			}
		});

	Get.BindLambda(
		[this]()
		{
			if (bool* ContainerPtrToValuePtr = Property->ContainerPtrToValuePtr<bool>(Object ))
			{
				return *ContainerPtrToValuePtr;
			}

			return false;
		});
}
