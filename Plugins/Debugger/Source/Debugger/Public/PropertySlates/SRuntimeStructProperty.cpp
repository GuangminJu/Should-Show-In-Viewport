#include "SRuntimeStructProperty.h"

void SRuntimeStructProperty::SetStruct(const TObjectPtr<UScriptStruct>& InStruct) const
{
	ViewportDetails->SetStruct(InStruct);
}

void SRuntimeStructProperty::SetObjects(const TArray<UObject*>& InObjects) const
{
	ViewportDetails->SetObjects(InObjects);
}
