// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeWithVoteMap.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
class UAbilitySystemComponent;


UCLASS()
class TASK4_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AMyPlayerState();
	UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }

	UFUNCTION()
	void OnRepMovementChanged();

	UFUNCTION()
	void OnDeathStateChanged();

	UPROPERTY(ReplicatedUsing = OnDeathStateChanged)
	bool bIsDead = false;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
	UPROPERTY(VisibleAnywhere)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(ReplicatedUsing=OnRepMovementChanged)
	bool bCanMove;
};
