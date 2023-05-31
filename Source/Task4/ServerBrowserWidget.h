// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MultiplayerLobbyWidget.h"
#include "ServerBrowserLineWidget.h"

#include "ServerBrowserWidget.generated.h"

UCLASS()
class TASK4_API UServerBrowserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* RefreshButton;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* ServerBox;

	void Refresh();

private:
	UPROPERTY(Transient)
	TArray<UServerBrowserLineWidget*> LineWidgets;

	UFUNCTION()
	void OnSessionCreated(bool Success);

	UFUNCTION()
	void OnHostButtonPressed();

	UFUNCTION()
	void OnCloseButtonPressed();

	UFUNCTION()
	void OnRefreshButtonClicked();

	UFUNCTION()
	void OnSessionFound(bool Successful);

	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UMultiplayerLobbyWidget> LobbyWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UServerBrowserLineWidget> LineWidget;

};
