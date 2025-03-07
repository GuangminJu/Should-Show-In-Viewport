#pragma once

#include "PropertySlates/SRuntimePropertySlateBase.h"
#include "Widgets/Layout/SWrapBox.h"

class SRuntimeViewportDetails : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRuntimeViewportDetails)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	void SetObjects(const TArray<UObject*>& InObjects);

	TArray<AActor*> GetActors() const;
	TArray<UObject*> GetObjects() const;


	TArray<TWeakObjectPtr<UObject>> Objects;
	TWeakObjectPtr<UClass> BaseClass;
	TSharedPtr<SOverlay> Overlay;
	TSharedPtr<SWrapBox> WrapBox;
	
	static TMap<FString, TFunction<TSharedPtr<SRuntimePropertySlateBase>()>> RuntimePropertyCreators;
	static TArray<TSharedPtr<SRuntimePropertySlateBase>> GetPropertySlates(const UClass* InClass, UObject* InObject);
};
