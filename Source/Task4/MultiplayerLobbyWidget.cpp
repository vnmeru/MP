// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerLobbyWidget.h"

#include "GameSessionSubsystem.h"
#include "LobbyGameState.h"
#include "LobbyPlayerState.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"

void UMultiplayerLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	ReadyButton->OnPressed.AddUniqueDynamic(this, &ThisClass::Ready);
	CloseServerButton->OnPressed.AddUniqueDynamic(this, &ThisClass::Leave);
	
	const UWorld* World = GetWorld();
	if(World)
	{
		ALobbyGameState* LobbyGameState = World->GetGameState<ALobbyGameState>();
		
		if(LobbyGameState)
		{
			RefreshList(LobbyGameState->PlayerArray);
			LobbyGameState->OnPlayerListRefreshEvent.AddUniqueDynamic(this, &ThisClass::RefreshList);
		}
	}
}
void UMultiplayerLobbyWidget::Ready()
{
	UWorld* World = GetWorld();
	if(World)
	{
		APlayerController* MyController = World->GetFirstPlayerController();
		ALobbyPlayerState* PlayerState = MyController->GetPlayerState<ALobbyPlayerState>();
		PlayerState->Server_ToggleReadyState();
	}
}
void UMultiplayerLobbyWidget::Leave()
{
	const UWorld* World = GetWorld();
	if (World)
	{
		UGameSessionSubsystem* GameSession = UGameplayStatics::GetGameInstance(World)->GetSubsystem<UGameSessionSubsystem>();
		if (GameSession)
		{
			GameSession->OnDestroySessionCompleteEvent.AddUniqueDynamic(this, &ThisClass::OnLeft);
			GameSession->DestroySession();
		}
	}
}

void UMultiplayerLobbyWidget::OnLeft(bool Success)
{
	UWorld* World = GetWorld();
	if(World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if(PlayerController)
		{
			PlayerController->ClientTravel("MenuLevel", TRAVEL_Absolute);
		}
	}
}

void UMultiplayerLobbyWidget::RefreshList(TArray<APlayerState*> PlayerList)
{
	PlayerVerticalBox->ClearChildren();
	for (APlayerState* PlayerState : PlayerList)
	{
		const ALobbyPlayerState* LobbyPlayerState = Cast<ALobbyPlayerState>(PlayerState);
		if(LobbyPlayerState)
		{
			UTextBlock* TextBlock = WidgetTree->ConstructWidget<UTextBlock>();
			TextBlock->SetText(FText::FromString(LobbyPlayerState->GetPlayerName()));

			if(LobbyPlayerState->bReady)
			{
				TextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
			}
			else
			{
				TextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
			}
			
			PlayerVerticalBox->AddChildToVerticalBox(TextBlock);
		}
	}
}
