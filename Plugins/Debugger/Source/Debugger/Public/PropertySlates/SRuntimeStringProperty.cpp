
#include "SRuntimeStringProperty.h"

void SRuntimeStringProperty::Construct(const FArguments& InArgs)
{
	TSRuntimePropertySlateBase<FString>::Construct(InArgs);

	ChildSlot
	[
		SNew(SEditableTextBox)
		.Text_Lambda([this]()-> FText
		{
			return FText::FromString(GetValue());
		})
		.OnTextCommitted_Lambda([this](const FText& InText, ETextCommit::Type InCommitType)
		{
			SetValue(InText.ToString());
		})
	];
}

void SRuntimeStringProperty::SetProperty(FProperty* InProperty, void* InObject)
{
	TSRuntimePropertySlateBase<FString>::SetProperty(InProperty, InObject);

	Set.BindLambda([this](const FString& InValue)
	{
		if (Property)
		{
			if (FString* ContainerPtrToValuePtr = Property->ContainerPtrToValuePtr<FString>(Object))
			{
				*ContainerPtrToValuePtr = InValue;
			}
		}
	});
	
	Get.BindLambda([this]()-> FString
	{
		if (Property)
		{
			if (FString* ContainerPtrToValuePtr = Property->ContainerPtrToValuePtr<FString>(Object))
			{
				return *ContainerPtrToValuePtr;
			}
		}
		return FString();
	});
}
