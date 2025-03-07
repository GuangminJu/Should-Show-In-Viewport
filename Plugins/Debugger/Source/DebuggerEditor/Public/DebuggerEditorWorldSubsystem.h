// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DebuggerEditorWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class DEBUGGEREDITOR_API UDebuggerEditorWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
};
