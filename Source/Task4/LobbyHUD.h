// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerLobbyWidget.h"
#include "GameFramework/HUD.h"
#include "LobbyHUD.generated.h"

UCLASS()
class TASK4_API ALobbyHUD : public AHUD
{
	GENERATED_BODY()
public:
	void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UMultiplayerLobbyWidget> LobbyWidget;

	UPROPERTY(Transient)
	UMultiplayerLobbyWidget* Lobby;
};
