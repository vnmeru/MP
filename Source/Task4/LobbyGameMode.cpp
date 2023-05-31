// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "GameSessionSubsystem.h"
#include "LobbyGameState.h"
#include "LobbyHUD.h"
#include "LobbyPlayerState.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "GameFramework/GameState.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	if(IsRunningDedicatedServer())
	{
		const UWorld* World = GetWorld();
		if (World)
		{
			UGameSessionSubsystem* GameSessionSubsystem = UGameplayStatics::GetGameInstance(World)->GetSubsystem<UGameSessionSubsystem>();
			if (GameSessionSubsystem)
			{
				GameSessionSubsystem->OnCreateSessionCompleteEvent.AddUniqueDynamic(this, &ThisClass::OnSessionCreated);
				GameSessionSubsystem->CreateSession(5, true);
			}
		}
	}
}

void ALobbyGameMode::OnSessionCreated(bool bSuccess)
{
	if (bSuccess)
	{
		UE_LOG(LogTemp, Display, TEXT("ALobbyGameMode::OnSessionCreated -> Session has been created!"));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("ALobbyGameMode::OnSessionCreated -> Failed to create a sessions!"));
	}
}
