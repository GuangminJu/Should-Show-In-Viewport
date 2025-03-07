#pragma once
#include "SRuntimePropertySlateBase.h"

class SRuntimeStringProperty : public TSRuntimePropertySlateBase<FString>
{
public:
	virtual void Construct(const FArguments& InArgs) override;
	virtual void SetProperty(FProperty* InProperty, UObject* InObject) override;
};
