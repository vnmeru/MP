// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LeaderboardWidget.h"
#include "Blueprint/UserWidget.h"
#include "ServerBrowserWidget.h"
#include "SettingsWidget.h"
#include "MenuWidget.generated.h"

UCLASS()
class TASK4_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ULeaderboardWidget> LeaderBoard;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UServerBrowserWidget> ServerBrowser;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<USettingsWidget> Settings;


	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MultiplayerButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* LeaderboardButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CloseButton;

private:

	UFUNCTION()
	void OnStartButtonClicked();

	UFUNCTION()
	void OnLeaderboardButtonClicked();

	UFUNCTION()
	void OnCloseButtonClicked();

	UFUNCTION()
	void OnMultiplayerButtonClicked();

	UFUNCTION()
	void OnSettingsButtonClicked();

	void NativeConstruct() override;

private:

	UPROPERTY(Transient)
	ULeaderboardWidget* LeaderboardWidget;

	UPROPERTY(Transient)
	USettingsWidget* SettingsWidget;

	UPROPERTY(Transient)
	UServerBrowserWidget* ServerBrowserWidget;
};