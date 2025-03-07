#pragma once
#include "SRuntimePropertySlateBase.h"

class SRuntimeRotatorProperty : public TSRuntimePropertySlateBase<FRotator>
{
public:
	virtual void Construct(const FArguments& InArgs) override;
	virtual void SetProperty(FProperty* InProperty, void* InObject) override;
};
