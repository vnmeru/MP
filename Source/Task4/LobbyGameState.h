// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LobbyGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerListRefresh,TArray<APlayerState*>, PlayerList);

UCLASS()
class TASK4_API ALobbyGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	FOnPlayerListRefresh OnPlayerListRefreshEvent;
private:
	virtual void AddPlayerState(APlayerState* PlayerState) override;
	virtual void RemovePlayerState(APlayerState* PlayerState) override;
public:
	void CheckStart();
};
