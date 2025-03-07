#pragma once
#include "SRuntimePropertySlateBase.h"

class SRuntimeBoolProperty : public TSRuntimePropertySlateBase<bool>
{
public:
	virtual void Construct(const FArguments& InArgs) override;
	virtual void SetProperty(FProperty* InProperty, void* InObject) override;
};
