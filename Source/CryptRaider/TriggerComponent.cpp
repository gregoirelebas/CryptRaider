// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

AActor* UTriggerComponent::GetKeyActor() const
{
	TArray<AActor*> overlappingActors;
	GetOverlappingActors(overlappingActors);

	for (AActor* actor : overlappingActors)
	{
		if (actor->ActorHasTag(_keyTag))
			return actor;
	}

	return nullptr;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!_isTriggered)
	{
		AActor* keyActor = GetKeyActor();
		if (keyActor != nullptr)
		{
			_isTriggered = true;

			UPrimitiveComponent* keyPrimitive = Cast<UPrimitiveComponent>(keyActor->GetRootComponent());
			if (keyPrimitive != nullptr)
				keyPrimitive->SetSimulatePhysics(false);

			if (_keyPosition != nullptr)
			{
				keyActor->AttachToComponent(_keyPosition, FAttachmentTransformRules::KeepRelativeTransform);
				keyActor->SetActorLocationAndRotation(_keyPosition->GetComponentLocation(), _keyPosition->GetComponentRotation());
			}

			if (_mover != nullptr)
				_mover->SetCanMove(true);
		}
	}
}

void UTriggerComponent::SetMover(UMover* mover)
{
	_mover = mover;
}

void UTriggerComponent::SetKeyPosition(USceneComponent* keyPosition)
{
	_keyPosition = keyPosition;
}
