// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Grabber.generated.h"

#define ECC_Grabber ECC_GameTraceChannel2

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UGrabber();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void Grab();

    UFUNCTION(BlueprintCallable)
    void Release();

private:
    UPhysicsHandleComponent* _physicHandle;
    UPrimitiveComponent* _grabbedComponent;

    UPROPERTY(EditAnywhere)
    float _grabDistance = 300.0f;

    UPROPERTY(EditAnywhere)
    float _grabRadius = 40.0f;

    bool GetGrabbableInReach(FHitResult& hitResult);
};
