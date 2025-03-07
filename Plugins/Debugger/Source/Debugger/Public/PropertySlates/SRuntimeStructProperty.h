#pragma once
#include "SRuntimePropertySlateBase.h"
#include "SRuntimeViewportDetails.h"

class SRuntimeStructProperty : public SRuntimePropertySlateBase
{
public:
	SLATE_BEGIN_ARGS(SRuntimeStructProperty)
	{
	}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		ChildSlot
		[
			SAssignNew(ViewportDetails, SRuntimeViewportDetails)
		];
	}
	void SetStruct(const TObjectPtr<UScriptStruct>& InStruct) const;
	void SetObjects(const TArray<UObject*>& InObjects) const;

	TSharedPtr<SRuntimeViewportDetails> ViewportDetails;
};
