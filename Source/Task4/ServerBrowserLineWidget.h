// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "ServerBrowserLineWidget.generated.h"

UCLASS()
class TASK4_API UServerBrowserLineWidget : public UUserWidget
{
	
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerNameText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayersText;

	FOnlineSessionSearchResult* SessionResult;

	UFUNCTION()
	void Join();

	UFUNCTION()
	void OnJoin(bool Success);

	virtual void NativeConstruct() override;
};
