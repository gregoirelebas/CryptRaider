// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> overlappingActors;
	GetOverlappingActors(overlappingActors);

	if (overlappingActors.Num() > 0)
	{
		FString name = overlappingActors[0]->GetActorNameOrLabel();
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, name);
	}
}
