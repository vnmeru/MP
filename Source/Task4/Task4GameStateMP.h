// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Net/UnrealNetwork.h"
#include "Task4GameStateMP.generated.h"

UCLASS()
class TASK4_API ATask4GameStateMP : public AGameState
{
	GENERATED_BODY()

private:
	ATask4GameStateMP();
	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
public:

	UPROPERTY(Replicated)
	bool bIsStarted = false;

	UPROPERTY(Replicated)
	float StartTime;

	float GetRoundTime() const;

	virtual void RemovePlayerState(APlayerState* PlayerState) override;
};
