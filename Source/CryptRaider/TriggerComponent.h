// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"

#include "TriggerComponent.generated.h"

/**
 *
 */
UCLASS(ClassGroup = Custom, meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UTriggerComponent();

private:
	UPROPERTY(EditAnywhere)
	FName _keyTag;

	UMover* _mover;

	USceneComponent* _keyPosition;

	bool _isTriggered = false;

private:
	AActor* GetKeyActor() const;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMover(UMover* mover);

	UFUNCTION(BlueprintCallable)
	void SetKeyPosition(USceneComponent* keyPosition);
};
