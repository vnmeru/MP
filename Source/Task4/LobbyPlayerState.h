// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LobbyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TASK4_API ALobbyPlayerState : public APlayerState
{
	GENERATED_BODY()

	ALobbyPlayerState();

public:
	UPROPERTY(ReplicatedUsing=OnRep_ReadyStateChanged)
	bool bReady = false;

	UFUNCTION(Server, Reliable)
	void Server_ToggleReadyState();

private:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_ReadyStateChanged();

	virtual void OnRep_PlayerName() override;

	void RefreshPlayerList();
};
