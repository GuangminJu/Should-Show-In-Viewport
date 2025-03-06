// Fill out your copyright notice in the Description page of Project Settings.


#include "DetailsViewWidgetComponent.h"

#include "LevelEditor.h"
#include "SLevelViewport.h"


void UDetailsViewWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	SetWidgetSpace(EWidgetSpace::Screen);
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(
		TEXT("PropertyEditor"));
	
	DetailView = SNew(SInViewportDetails);
	SetSlateWidget(DetailView);
}

void UDetailsViewWidgetComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsSelectedActor())
	{
		return;
	}

	SetWorldLocation(GetWidgetLocation());
}

bool UDetailsViewWidgetComponent::IsSelectedActor() const
{
	return !!DetailView->GetSelectedActorInEditor();
}

FVector UDetailsViewWidgetComponent::GetWidgetLocation() const
{
	AActor* SelectedActorInEditor = DetailView->GetSelectedActorInEditor();
	if (!SelectedActorInEditor)
	{
		return FVector::ZeroVector;
	}
	return SelectedActorInEditor->GetActorLocation();
}

void UDetailsViewWidgetComponent::SetObject(UObject* InObject) const
{
	DetailView->SetObjects({InObject});
}

bool UDetailsViewWidgetComponent::IsSelected(const UObject* InObject) const
{
	return InObject == DetailView->GetSelectedActorInEditor();
}

bool UDetailsViewWidgetComponent::IsSelectedObject() const
{
	return IsSelectedActor();
}

void UDetailsViewWidgetComponent::ClearObject(const UObject* InObject) const
{
	if (IsSelected(InObject))
	{
		DetailView->SetObjects({});
	}
}
