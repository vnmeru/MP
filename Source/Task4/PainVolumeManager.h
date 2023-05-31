// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PainCausingVolume.h"
#include "Engine/EngineTypes.h"
#include "PainVolumeManager.generated.h"

UCLASS()
class TASK4_API APainVolumeManager : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	APainCausingVolume* PainCausingVolume;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	APainVolumeManager();

	void OnTimerFired();

private:
	FTimerHandle TimerHandle;
};