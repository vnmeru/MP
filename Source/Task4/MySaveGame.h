// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

USTRUCT(BlueprintType)
struct FLeaderBoardEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite )
	FString PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Score;
};

UCLASS(BlueprintType)
class TASK4_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FLeaderBoardEntry> LeaderBoardEntries;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText NickName;
};