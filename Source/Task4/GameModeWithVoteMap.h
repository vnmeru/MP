// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameModeWithVoteMap.generated.h"

UENUM(BlueprintType)
enum class VoteMap : uint8 {
	NormalGame = 0	UMETA(DisplayName = "Normal"),
	ShieldGame = 1	UMETA(DisplayName = "Shield"),
	Max = 2		    UMETA(Hidden),
	None = 3		UMETA(DisplayName = "None"),

};

struct VoteResult
{
	VoteResult(VoteMap GameMode)
	{
		SelectedGameMode = GameMode;
		Occurences = 1;
	};
	bool operator==(const VoteResult& Other) const
	{
		return this->SelectedGameMode == Other.SelectedGameMode;
	};
	VoteMap SelectedGameMode;
	int32   Occurences;
};

UCLASS()
class TASK4_API AGameModeWithVoteMap : public AGameMode
{
	GENERATED_BODY()
public:

	UFUNCTION()
	void OnVoteTimerUpdate();

	virtual void EndMatch() override;

	void StartMapVote();

	virtual bool ReadyToEndMatch_Implementation() override;

	virtual void StartMatch() override;

	UPROPERTY(EditDefaultsOnly)
	float VoteTimeRemeaning = 5;

	UPROPERTY(EditDefaultsOnly)
	float VoteNotificationDelay = 5;

	UFUNCTION()
	void OnCharacterDeath(float Time);

private:
	FTimerHandle VoteTimerHandler;

	FTimerHandle NextMapTimerHandler;

	VoteMap NextMap;

	bool bAllPlayersAreDead = false;
};
