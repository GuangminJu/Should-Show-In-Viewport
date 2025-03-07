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
	void SetStruct(const TObjectPtr<UScriptStruct>& InStruct);
	void SetProperty(FProperty* InProperty, void* InRaw);

	TArray<AActor*> GetActors() const;
	TArray<UObject*> GetObjects() const;

	TArray<TWeakObjectPtr<UObject>> Objects;
	TWeakObjectPtr<UClass> BaseClass;
	TSharedPtr<SOverlay> Overlay;
	TSharedPtr<SWrapBox> WrapBox;
	TWeakObjectPtr<UScriptStruct> Struct;
	
	float NameWidth = 100.0f;
	bool DisplayName = true;
	
	void SetRuntimePropertySlate(const TArray<TSharedPtr<SRuntimePropertySlateBase>>& CompoundWidgets) const;
	
	static TMap<FString, TFunction<TSharedPtr<SRuntimePropertySlateBase>()>> RuntimePropertyCreators;
	static TArray<TSharedPtr<SRuntimePropertySlateBase>> GetPropertySlates(const UClass* InClass, UObject* InObject);
	static void GetPropertySlates(void* InObject, FProperty* It, TArray<TSharedPtr<SRuntimePropertySlateBase>>& CompoundWidgets);
	static bool HasPropertyCreator(const FProperty* It);
};
