#include "SRuntimeRotatorProperty.h"

#include "Widgets/Input/SRotatorInputBox.h"

void SRuntimeRotatorProperty::Construct(const FArguments& InArgs)
{
	TSRuntimePropertySlateBase<FRotator>::Construct(InArgs);

	ChildSlot
	[
		SNew(SNumericRotatorInputBox<double>)
		.OnPitchCommitted_Lambda(
			[this](double InValue, ETextCommit::Type InType)
			{
				SetValue(FRotator(InValue, GetValue().Yaw, GetValue().Roll));
			})
		.OnYawCommitted_Lambda(
			[this](double InValue, ETextCommit::Type InType)
			{
				SetValue(FRotator(GetValue().Pitch, InValue, GetValue().Roll));
			})
		.OnRollCommitted_Lambda(
			[this](double InValue, ETextCommit::Type InType)
			{
				SetValue(FRotator(GetValue().Pitch, GetValue().Yaw, InValue));
			})
		.Pitch_Lambda(
			[this]() -> double
			{
				return GetValue().Pitch;
			})
		.Yaw_Lambda(
			[this]() -> double
			{
				return GetValue().Yaw;
			})
		.Roll_Lambda(
			[this]() -> double
			{
				return GetValue().Roll;
			})
	];
}

void SRuntimeRotatorProperty::SetProperty(FProperty* InProperty, void* InObject)
{
	TSRuntimePropertySlateBase<FRotator>::SetProperty(InProperty, InObject);

	Set.BindLambda(
		[this](const FRotator& InValue)
		{
			if (FRotator* ContainerPtrToValuePtr = Property->ContainerPtrToValuePtr<FRotator>(Object))
			{
				*ContainerPtrToValuePtr = InValue;
			}
		});

	Get.BindLambda(
		[this]()
		{
			if (FRotator* ContainerPtrToValuePtr = Property->ContainerPtrToValuePtr<FRotator>(Object))
			{
				return *ContainerPtrToValuePtr;
			}

			return FRotator::ZeroRotator;
		});
}
