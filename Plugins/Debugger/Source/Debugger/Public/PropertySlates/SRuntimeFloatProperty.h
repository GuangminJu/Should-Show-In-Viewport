#pragma once
#include "SRuntimePropertySlateBase.h"

class SRuntimeFloatProperty : public TSRuntimePropertySlateBase<float>
{
public:
	virtual void Construct(const FArguments& InArgs) override;
	virtual void SetProperty(FProperty* InProperty, void* InObject) override;
};
