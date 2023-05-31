// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MultiplayerLobbyWidget.generated.h"

UCLASS()
class TASK4_API UMultiplayerLobbyWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* PlayerVerticalBox;

	UPROPERTY(meta = (BindWidget))
	class UButton* ReadyButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CloseServerButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CloseServerText;

private:

	UFUNCTION()
	void Ready();

	UFUNCTION()
	void Leave();

	UFUNCTION()
	void OnLeft(bool Success);

	UFUNCTION()
	void RefreshList(TArray<APlayerState*> PlayerList);

	virtual void NativeConstruct() override;
};
