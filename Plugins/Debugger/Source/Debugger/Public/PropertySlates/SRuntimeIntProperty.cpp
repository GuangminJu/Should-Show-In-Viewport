#include "SRuntimeIntProperty.h"

#include "Widgets/Input/SNumericEntryBox.h"

void SRuntimeIntProperty::Construct(const FArguments& InArgs)
{
	TSRuntimePropertySlateBase::Construct(InArgs);

	ChildSlot
	[
		SNew(SNumericEntryBox<int32>)
		.AllowSpin(true)
		.OnValueCommitted_Lambda(
			[this](const int32 InValue, ETextCommit::Type InType)
			{
				SetValue(InValue);
			})
		.Value_Lambda(
			[this]()-> int32
			{
				return GetValue();
			})
	];
}

void SRuntimeIntProperty::SetProperty(FProperty* InProperty, UObject* InObject)
{
	TSRuntimePropertySlateBase<int>::SetProperty(InProperty, InObject);

	Set.BindLambda(
		[this](int32 InValue)
		{
			if (int32* ContainerPtrToValuePtr = Property->ContainerPtrToValuePtr<int32>(Object.Get()))
			{
				*ContainerPtrToValuePtr = InValue;
			}
		});
	Get.BindLambda(
		[this]()
		{
			if (int32* ContainerPtrToValuePtr = Property->ContainerPtrToValuePtr<int32>(Object.Get()))
			{
				return *ContainerPtrToValuePtr;
			}

			return 0;
		});
}
