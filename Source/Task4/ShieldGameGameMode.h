// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeWithVoteMap.h"
#include "GameFramework/GameMode.h"
#include "ShieldGameGameMode.generated.h"


UENUM(BlueprintType)
enum class AttackColor : uint8 {
	Red = 0		UMETA(DisplayName = "Red"),
	Green = 1	UMETA(DisplayName = "Green"),
	Blue = 2	UMETA(DisplayName = "Blue"),
	Max = 3		UMETA(Hidden),
	None = 4	UMETA(Hidden)
};

UCLASS()
class TASK4_API AShieldGameGameMode : public AGameModeWithVoteMap
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

	UFUNCTION()
	void FireMissiles();

	virtual bool ReadyToStartMatch_Implementation() override;

	virtual void StartMatch() override;

private:
	FTimerHandle FireTimerHandle;
	bool bMatchStarted = false;
};
