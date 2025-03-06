// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"

#include "SInViewportDetails.h"

#include "DetailsViewWidgetComponent.generated.h"

UCLASS()
class UDetailsViewWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;
	bool IsSelectedActor() const;
	FVector GetWidgetLocation() const;
	void SetObject(UObject* InObject) const;
	bool IsSelected(const UObject* InObject) const;
	bool IsSelectedObject() const;
	void ClearObject(const UObject* InObject) const;

	bool bSearch = false;
private:
	TSharedPtr<SInViewportDetails> DetailView;
};