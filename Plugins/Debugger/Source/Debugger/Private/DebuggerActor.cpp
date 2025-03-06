// Fill out your copyright notice in the Description page of Project Settings.


#include "DebuggerActor.h"


// Sets default values
ADebuggerActor::ADebuggerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADebuggerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADebuggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UDetailsViewWidgetComponent* ADebuggerActor::CreateWidgetComponent()
{
	UDetailsViewWidgetComponent* WidgetComponent = NewObject<UDetailsViewWidgetComponent>(this);
	WidgetComponent->RegisterComponent();
	return WidgetComponent;
}
