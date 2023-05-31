// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LeaderboardLineWidget.generated.h"

UCLASS()
class TASK4_API ULeaderboardLineWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameBlock;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ScoreBlock;
};