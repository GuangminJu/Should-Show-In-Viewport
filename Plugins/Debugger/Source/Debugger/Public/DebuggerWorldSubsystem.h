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
class DEBUGGER_API UDebuggerWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
public:
	
	UFUNCTION(BlueprintCallable, Category = "Debugger")
	void OpenDebugger(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Debugger")
	void CloseDebugger(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Debugger")
	ADebuggerActor* GetDebuggerActor() const;
	
	UPROPERTY()
	TArray<UDetailsViewWidgetComponent*> WidgetComponents;

	UPROPERTY()
	ADebuggerActor* DebuggerActor;
};
