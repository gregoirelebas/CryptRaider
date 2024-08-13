// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
    Super::BeginPlay();

    // ...

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGrabber::Grab()
{
    FVector start = GetComponentLocation();
    FVector end = start + GetForwardVector() * _grabDistance;

    FCollisionShape sphereShape = FCollisionShape::MakeSphere(_grabRadius);

    FHitResult hitResult;
    if (GetWorld()->SweepSingleByChannel(hitResult, start, end, FQuat::Identity, ECC_Grabber, sphereShape))
    {
        AActor* actor = hitResult.GetActor();
        UE_LOG(LogTemp, Display, TEXT("%s"), *actor->GetActorNameOrLabel());
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("No hit"));
    }
}

void UGrabber::Release()
{
    UE_LOG(LogTemp, Display, TEXT("Released"));
}

