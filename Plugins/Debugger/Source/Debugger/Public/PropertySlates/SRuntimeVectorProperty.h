#pragma once
#include "SRuntimePropertySlateBase.h"

class SRuntimeVectorProperty : public TSRuntimePropertySlateBase<FVector>
{
public:
	virtual void Construct(const FArguments& InArgs) override;
	virtual void SetProperty(FProperty* InProperty, void* InObject) override;
};
