#include "SRuntimeFloatProperty.h"

#include "Widgets/Input/SNumericEntryBox.h"

void SRuntimeFloatProperty::Construct(const FArguments& InArgs)
{
	TSRuntimePropertySlateBase<float>::Construct(InArgs);

	ChildSlot
	[
		SNew(SNumericEntryBox<float>)
		.Value_Lambda([this]() { return GetValue(); })
		.OnValueChanged_Lambda([this](float InValue) { SetValue(InValue); })
	];
}

void SRuntimeFloatProperty::SetProperty(FProperty* InProperty, void* InObject)
{
	TSRuntimePropertySlateBase<float>::SetProperty(InProperty, InObject);

	Set.BindLambda(
		[this](float InValue)
		{
			if (float* ContainerPtrToValuePtr = Property->ContainerPtrToValuePtr<float>(Object ))
			{
				*ContainerPtrToValuePtr = InValue;
			}
		});

	Get.BindLambda(
		[this]()
		{
			if (float* ContainerPtrToValuePtr = Property->ContainerPtrToValuePtr<float>(Object ))
			{
				return *ContainerPtrToValuePtr;
			}

			return 0.0f;
		});
}
