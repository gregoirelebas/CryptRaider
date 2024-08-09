// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetMathLibrary.h"
#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called when the game starts
void UMover::BeginPlay()
{
    Super::BeginPlay();

    _owner = GetOwner();
    _startLocation = _owner->GetActorLocation();
}

// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FVector currentLocation = _owner->GetActorLocation();
    FVector targetLocation = _startLocation + _moveOffset;

    float speed = FVector::Distance(_startLocation, targetLocation) / _moveTime;

    FVector newLocation = UKismetMathLibrary::VInterpTo_Constant(currentLocation, targetLocation, DeltaTime, speed);

    _owner->SetActorLocation(newLocation);
}
