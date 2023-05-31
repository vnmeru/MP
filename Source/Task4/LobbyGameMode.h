// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerLobbyWidget.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

UCLASS()
class TASK4_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSessionCreated(bool bSuccess);
};
