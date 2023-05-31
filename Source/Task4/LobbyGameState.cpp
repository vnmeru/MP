// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameState.h"
#include "LobbyPlayerState.h"

void ALobbyGameState::RemovePlayerState(APlayerState* PlayerState)
{
	Super::RemovePlayerState(PlayerState);
	OnPlayerListRefreshEvent.Broadcast(PlayerArray);
}

void ALobbyGameState::CheckStart()
{
	if(GetLocalRole() != ROLE_Authority)
	{
		return;
	}
	for (APlayerState* PlayerState : PlayerArray)
	{
		const ALobbyPlayerState* LobbyPlayerState = Cast<ALobbyPlayerState>(PlayerState);
		if(!LobbyPlayerState->bReady)
		{
			return;
		}
	}

	//Everyone is ready!
	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel("NormalGameLevel");
	}
}

void ALobbyGameState::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);
	OnPlayerListRefreshEvent.Broadcast(PlayerArray);
}

