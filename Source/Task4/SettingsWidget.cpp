// Fill out your copyright notice in the Description page of Project Settings.

#include "SettingsWidget.h"

#include "MySaveGame.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

void USettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UMySaveGame* LoadedGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Leaderboard"), 0));

	if (LoadedGame)
	{
		NameTextBox->SetText(LoadedGame->NickName);
	}

	SaveButton->OnPressed.AddUniqueDynamic(this, &ThisClass::Save);
	CloseButton->OnPressed.AddUniqueDynamic(this, &ThisClass::OnClose);
}

void USettingsWidget::Save()
{
	UMySaveGame* LoadedGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Leaderboard"), 0));
	if (UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass())))
	{
		// Set data on the savegame object.
		if (LoadedGame)
		{
			SaveGameInstance->LeaderBoardEntries = LoadedGame->LeaderBoardEntries;
			SaveGameInstance->NickName = NameTextBox->GetText();

		}
		// Save the data immediately.
		if (!UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Leaderboard"), 0))
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to save a nickname"));
		}
	}
}
void USettingsWidget::OnClose()
{
	SetIsEnabled(false);
	SetVisibility(ESlateVisibility::Collapsed);
}