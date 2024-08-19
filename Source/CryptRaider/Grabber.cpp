// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"


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

    _physicHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

    if (_physicHandle == nullptr)
        UE_LOG(LogTemp, Warning, TEXT("No PhysicsHandle component was found!"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (_physicHandle == nullptr || _grabbedComponent == nullptr)
        return;

    FVector targetLocation = GetComponentLocation() + GetForwardVector() * _grabDistance;
    _physicHandle->SetTargetLocationAndRotation(targetLocation, _grabbedComponent->GetComponentRotation());
}

void UGrabber::Grab()
{
    FHitResult hitResult;
    if (GetGrabbableInReach(hitResult))
    {
        _grabbedComponent = hitResult.GetComponent();
        _grabbedComponent->WakeAllRigidBodies();
        _grabbedComponent->GetOwner()->Tags.Add(_grabTag);
        _grabbedComponent->GetOwner()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        _grabbedComponent->SetSimulatePhysics(true);

        _physicHandle->GrabComponentAtLocationWithRotation(_grabbedComponent, NAME_None, hitResult.ImpactPoint, _grabbedComponent->GetComponentRotation());
    }
}

void UGrabber::Release()
{
    if (_grabbedComponent != nullptr)
    {
        _grabbedComponent->GetOwner()->Tags.Remove(_grabTag);

        _physicHandle->ReleaseComponent();
        _grabbedComponent = nullptr;
    }
}

bool UGrabber::GetGrabbableInReach(FHitResult& hitResult)
{
    FVector start = GetComponentLocation();
    FVector end = start + GetForwardVector() * _grabDistance;

    FCollisionShape sphereShape = FCollisionShape::MakeSphere(_grabRadius);

    return GetWorld()->SweepSingleByChannel(hitResult, start, end, FQuat::Identity, ECC_Grabber, sphereShape);
}

