// Fill out your copyright notice in the Description page of Project Settings.


#include "DebuggerEditorWorldSubsystem.h"

#include "DebuggerWorldSubsystem.h"
#include "Selection.h"

void UDebuggerEditorWorldSubsystem::Tick(float DeltaTime)
{
	UDebuggerWorldSubsystem* Debugger = GetWorld()->GetSubsystem<UDebuggerWorldSubsystem>();

#if WITH_EDITOR
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

		Debugger->OpenDebugger(Cast<AActor>(ActorIterator));
	}
#endif
}

TStatId UDebuggerEditorWorldSubsystem::GetStatId() const
{
	return TStatId();
}