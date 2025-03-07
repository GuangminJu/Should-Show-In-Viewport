#pragma once

#include "SRuntimePropertySlateBase.h"

class SRuntimeIntProperty : public TSRuntimePropertySlateBase<int32>
{
public:
	virtual void Construct(const FArguments& InArgs) override;
	virtual void SetProperty(FProperty* InProperty, void* InObject) override;
};
