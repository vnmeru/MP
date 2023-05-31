// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LeaderboardWidget.h"
#include "Blueprint/UserWidget.h"
#include "DeathScreenWidget.generated.h"

/**
 * Death Screen widget which will show EditableSaveBox and a button for saving current progress
 */
UCLASS()
class TASK4_API UDeathScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* SaveButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* NameBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ScoreBox;

	void SetTimeSurvived(float Time);

private:

	void NativeConstruct() override;

	UFUNCTION()
	void OnSave();

	UFUNCTION()
	void OnExit();

	bool bWasSaved = false;

	float TimeSurvived;
};
