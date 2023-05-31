// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MapVoteMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class TASK4_API UMapVoteMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimeRemeaningText;

	UPROPERTY(meta = (BindWidget))
	UButton* NormalGameVoteButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ShieldGameVoteButton;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void NormalGameVoted();

	UFUNCTION()
	void ShieldGameVoted();

	UFUNCTION(Client,Unreliable)
	void SetVoteTimer(int32 Time);
};
