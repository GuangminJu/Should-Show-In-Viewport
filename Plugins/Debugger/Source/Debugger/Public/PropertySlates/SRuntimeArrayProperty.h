#pragma once
#include "SRuntimePropertySlateBase.h"
#include "SRuntimeViewportDetails.h"

class SRuntimeArrayProperty : public SRuntimePropertySlateBase
{
public:
	SLATE_BEGIN_ARGS(SRuntimePropertySlateBase)
	{
	}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	virtual void SetProperty(FProperty* InProperty, void* InObject) override;

	TSharedPtr<SScrollBox> ScrollBox;
	FArrayProperty* ArrayProperty;

	TArray<TSharedPtr<SRuntimeViewportDetails>> PropertySlates;
};
