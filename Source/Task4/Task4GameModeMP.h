// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeWithVoteMap.h"
#include "HealthKit.h"
#include "GameFramework/GameMode.h"
#include "Task4GameModeMP.generated.h"


UCLASS()
class TASK4_API ATask4GameModeMP : public AGameModeWithVoteMap
{
	GENERATED_BODY()

private:
	ATask4GameModeMP();

	virtual void BeginPlay() override;

	virtual bool ReadyToStartMatch_Implementation() override;

	void Tick(float DeltaSeconds) override;

	void StartMatch() override;

	TArray<AHealthKit*> GetAllHealthKits();

public:
	UFUNCTION()
	void OnHealthKitCollision(AHealthKit* HealthKit);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> PlayerPawnClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHUD> GameHUDClass;

	bool bMatchStarted = false;
};
