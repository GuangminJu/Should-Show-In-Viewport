// Fill out your copyright notice in the Description page of Project Settings.


#include "DebuggerWorldSubsystem.h"

void UDebuggerWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	DebuggerActor = GetWorld()->SpawnActor<ADebuggerActor>();
}

bool UDebuggerWorldSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UDebuggerWorldSubsystem::OpenDebugger(AActor* InActor)
{
	UDetailsViewWidgetComponent* IdleDetailsViewWidgetComponent = nullptr;
	for (UDetailsViewWidgetComponent* DetailsViewWidgetComponent : WidgetComponents)
	{
		if (DetailsViewWidgetComponent->IsSelected(InActor))
		{
			return;
		}

		if (!IdleDetailsViewWidgetComponent && !DetailsViewWidgetComponent->IsSelectedObject())
		{
			IdleDetailsViewWidgetComponent = DetailsViewWidgetComponent;
		}
	}

	UDetailsViewWidgetComponent* DetailsViewWidgetComponent = IdleDetailsViewWidgetComponent;
	if (!DetailsViewWidgetComponent)
	{
		DetailsViewWidgetComponent = DebuggerActor->CreateWidgetComponent();
	}

	DetailsViewWidgetComponent->SetObject(InActor);
	WidgetComponents.Add(DetailsViewWidgetComponent);
}

void UDebuggerWorldSubsystem::CloseDebugger(AActor* InActor)
{
	for (UDetailsViewWidgetComponent* DetailsViewWidgetComponent : WidgetComponents)
	{
		if (DetailsViewWidgetComponent->IsSelected(InActor))
		{
			DetailsViewWidgetComponent->ClearObject(InActor);
			break;
		}
	}
}

ADebuggerActor* UDebuggerWorldSubsystem::GetDebuggerActor() const
{
	return DebuggerActor;
}
