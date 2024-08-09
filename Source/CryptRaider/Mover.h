// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "Mover.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UMover : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's propertiesF
    UMover();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere)
    FVector _moveOffset;

    UPROPERTY(EditAnywhere)
    float _moveTime = 4.0f;

    UPROPERTY(EditAnywhere)
    bool _canMove = false;

    AActor* _owner;
    FVector _startLocation;
};
