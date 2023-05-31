// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerController.h"

#include "LobbyPlayerState.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (IsLocalPlayerController())
	{
		//Set PlayerName
		const UMySaveGame* LoadedGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Leaderboard"), 0));
			
		if (LoadedGame)
		{
			SetPlayerName(LoadedGame->NickName.ToString());
		}
		else
		{
			SetPlayerName("Player");
		}
	}
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	SetInputMode(FInputModeUIOnly());
}

void ALobbyPlayerController::SetPlayerName_Implementation(const FString& Name)
{
	ALobbyPlayerState* LobbyPlayerState = Cast<ALobbyPlayerState>(PlayerState);
	if (LobbyPlayerState)
	{
		LobbyPlayerState->SetPlayerName(Name.IsEmpty() ? TEXT("Player") : Name );
	}
}