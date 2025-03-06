// Fill out your copyright notice in the Description page of Project Settings.


#include "DebuggerWorldSubsystem.h"

#include "Selection.h"

void UDebuggerWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	DebuggerActor = GetWorld()->SpawnActor<ADebuggerActor>();
}

bool UDebuggerWorldSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UDebuggerWorldSubsystem::Tick(float DeltaTime)
{
	if (!DebuggerActor)
	{
		return;
	}

	FSelectionIterator SelectedActorIterator = GEditor->GetSelectedActorIterator();
	while (SelectedActorIterator)
	{
		ON_SCOPE_EXIT
		{
			++SelectedActorIterator;
		};

		UObject* ActorIterator = *SelectedActorIterator;
		if (!ActorIterator)
		{
			continue;
		}

		OpenDebugger(Cast<AActor>(ActorIterator));
	}
}

TStatId UDebuggerWorldSubsystem::GetStatId() const
{
	return TStatId();
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
