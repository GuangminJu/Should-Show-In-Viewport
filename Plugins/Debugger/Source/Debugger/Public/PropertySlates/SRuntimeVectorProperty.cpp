
#include "SRuntimeVectorProperty.h"

#include "Math/NumericLimits.h"
#include "Widgets/Input/SVectorInputBox.h"

void SRuntimeVectorProperty::Construct(const FArguments& InArgs)
{
	TSRuntimePropertySlateBase::Construct(InArgs);

	ChildSlot
	[
		SNew(SNumericVectorInputBox<double>)
		.AllowSpin(true)
		.OnVectorCommitted_Lambda(
			[this](const FVector& InValue, ETextCommit::Type InType)
			{
				SetValue(InValue);
			})
		.Vector_Lambda(
			[this]()-> FVector
			{
				return GetValue();
			})
	];
}

void SRuntimeVectorProperty::SetProperty(FProperty* InProperty, void* InObject)
{
	TSRuntimePropertySlateBase::SetProperty(InProperty, InObject);

	Set.BindLambda(
		[this](const FVector& InValue)
		{
			if (FVector* ContainerPtrToValuePtr = Property->ContainerPtrToValuePtr<FVector>(Object))
			{
				*ContainerPtrToValuePtr = InValue;
			}
		});

	Get.BindLambda(
		[this]()
		{
			if (FVector* ContainerPtrToValuePtr = Property->ContainerPtrToValuePtr<FVector>(Object))
			{
				return *ContainerPtrToValuePtr;
			}

			return FVector::ZeroVector;
		});
}
