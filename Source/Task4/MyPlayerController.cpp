// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "AbilitySystemComponent.h"
#include "MapVoteMenuWidget.h"
#include "MyCharacter.h"
#include "MyPlayerState.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"

void AMyPlayerController::BeginPlay()
{
	bReplicates = true;
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
}

void AMyPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
}

void AMyPlayerController::Vote_Implementation(const VoteMap VoteMap)
{
	VotedMap = VoteMap;
}

void AMyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//REPLIFETIME(ThisClass, bIsDead);
	DOREPLIFETIME(ThisClass, VotedMap);
}

void AMyPlayerController::HideVoteMenu_Implementation()
{
	if (MapVoteMenuWidget)
	{
		MapVoteMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AMyPlayerController::ShowNextMapNotification_Implementation(const FString& String)
{
	if (MapVoteNotificationWidget)
	{
		MapVoteNotificationWidget->SetVisibility(ESlateVisibility::Visible);
		return;
	}

	MapVoteNotificationWidget = CreateWidget<UMapVoteNotification>(GetWorld(), MapVoteNotificationWidgetClass);

	if (MapVoteNotificationWidget)
	{
		MapVoteNotificationWidget->AddToViewport();
	}
	MapVoteNotificationWidget->NextMapText->SetText(FText::FromString(String));
}


void AMyPlayerController::SetMapVoteTimeRemeaning_Implementation(int32 Time)
{
	if (MapVoteMenuWidget)
	{
		MapVoteMenuWidget->SetVoteTimer(Time);
	}
}

void AMyPlayerController::ShowMapVote_Implementation()
{
	if (MapVoteMenuWidget)
	{
		MapVoteMenuWidget->SetVisibility(ESlateVisibility::Visible);
		return;
	}

	MapVoteMenuWidget = CreateWidget<UMapVoteMenuWidget>(GetWorld(), MapVoteMenuWidgetClass);

	if (MapVoteMenuWidget)
	{
		MapVoteMenuWidget->AddToViewport();
	}
}

void AMyPlayerController::SetPlayerName_Implementation(const FString& Name)
{
	AMyPlayerState* GamePlayerState = Cast<AMyPlayerState>(PlayerState);

	if (GamePlayerState)
	{
		GamePlayerState->SetPlayerName(Name.IsEmpty() ? TEXT("Player") : Name);
	}
}
