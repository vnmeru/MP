// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeWithVoteMap.h"
#include "PlayerHUDWidget.h"
#include "GameFramework/PlayerController.h"
#include "MapVoteNotification.h"
#include "Net/UnrealNetwork.h"

#include "MyPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthUpdated, float, Number);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStart);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDeath, float, Time);


UCLASS()
class TASK4_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	void AcknowledgePossession(APawn* P) override;

	UFUNCTION(Server, Reliable)
	void Vote(const VoteMap VoteMap);

	UFUNCTION(Client, Reliable)
	void HideVoteMenu();

	UFUNCTION(Client, Reliable)
	void ShowNextMapNotification(const FString& String);

	UFUNCTION(Client, Reliable)
	void SetMapVoteTimeRemeaning(int32 Time);

	UFUNCTION(Client, Reliable)
	void ShowMapVote();

	FOnHealthUpdated OnHealthUpdatedEvent;

	FCharacterDeath OnCharacterDeath;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDeathScreenWidget> DeathScreenWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPlayerHUDWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMapVoteNotification> MapVoteNotificationWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMapVoteMenuWidget> MapVoteMenuWidgetClass;

	UPROPERTY(Transient)
	UMapVoteNotification* MapVoteNotificationWidget;

	UPROPERTY(Transient)
	UMapVoteMenuWidget* MapVoteMenuWidget;

	FOnGameStart OnGameStartEvent;

	UPROPERTY(Replicated)
	VoteMap VotedMap;

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

private:

	UFUNCTION(Server, Reliable)
	void SetPlayerName(const FString& Name);
};
