// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DebuggerActor.h"
#include "Subsystems/WorldSubsystem.h"
#include "DebuggerWorldSubsystem.generated.h"

/**
 * 
 */

UCLASS()
class DEBUGGER_API UDebuggerWorldSubsystem : public UWorldSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;

	UFUNCTION(BlueprintCallable, Category = "Debugger")
	void OpenDebugger(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Debugger")
	void CloseDebugger(AActor* InActor);
	
	UPROPERTY()
	TArray<UDetailsViewWidgetComponent*> WidgetComponents;

	UPROPERTY()
	ADebuggerActor* DebuggerActor;
};
