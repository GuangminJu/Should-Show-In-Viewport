// Fill out your copyright notice in the Description page of Project Settings.


#include "DetailsViewWidgetComponent.h"

void UDetailsViewWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	SetWidgetSpace(EWidgetSpace::Screen);
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(
		TEXT("PropertyEditor"));
	
	DetailView = SNew(SRuntimeViewportDetails);
	SetSlateWidget(DetailView);
	SetDrawSize(FVector2D(400, 400));
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
	return DetailView->GetActors().Num() > 0;
}

FVector UDetailsViewWidgetComponent::GetWidgetLocation() const
{
	TArray<AActor*> Actors = DetailView->GetActors();
	if (Actors.Num() == 0)
	{
		return FVector::ZeroVector;
	}
	
	AActor* SelectedActorInEditor = Actors[0];
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
	TArray<UObject*> Objects = DetailView->GetObjects();
	return Objects.Contains(InObject);
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
