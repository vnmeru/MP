// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyPlayerState.h"

#include "LobbyGameMode.h"
#include "LobbyGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

ALobbyPlayerState::ALobbyPlayerState()
{
	bReplicates = true;
	bUseCustomPlayerNames = true;
}


void ALobbyPlayerState::OnRep_ReadyStateChanged()
{
	RefreshPlayerList();
}

void ALobbyPlayerState::OnRep_PlayerName()
{
	Super::OnRep_PlayerName();

	RefreshPlayerList();
}

void ALobbyPlayerState::RefreshPlayerList()
{
	const UWorld* World = GetWorld();
	if (World)
	{
		ALobbyGameState* LobbyGameState = World->GetGameState<ALobbyGameState>();

		if (LobbyGameState)
		{
			LobbyGameState->OnPlayerListRefreshEvent.Broadcast(LobbyGameState->PlayerArray);
		}
	}
}

void ALobbyPlayerState::Server_ToggleReadyState_Implementation()
{
	bReady = !bReady;
	OnRep_ReadyStateChanged();
	if (auto* World = GetWorld())
	{
		if( auto * LobbyGM = Cast<ALobbyGameState>(UGameplayStatics::GetGameState(World)))
		{
			LobbyGM->CheckStart();
		}
	}
}

void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, bReady);
}
