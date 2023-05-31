// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathScreenWidget.h"
#include "MySaveGame.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UDeathScreenWidget::SetTimeSurvived(float Time)
{
	TimeSurvived = Time;
	ScoreBox->SetText(FText::FromString(FString::Printf(TEXT("%.1f"),Time)));
}

void UDeathScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ExitButton->OnPressed.AddUniqueDynamic(this, &UDeathScreenWidget::OnExit);
	SaveButton->OnPressed.AddUniqueDynamic(this, &UDeathScreenWidget::OnSave);

	const UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* MyController = GetWorld()->GetFirstPlayerController();
		if (MyController)
		{
			MyController->SetInputMode(FInputModeUIOnly{});
			MyController->bShowMouseCursor = true;
			MyController->bEnableClickEvents = true;
			MyController->bEnableMouseOverEvents = true;

			NameBox->SetUserFocus(MyController);
		}
	}
}

void UDeathScreenWidget::OnExit()
{
	const UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "MenuLevel");
	}
}

void UDeathScreenWidget::OnSave()
{
	if (bWasSaved)
	{
		return;
	}

	FText Name = NameBox->GetText();
	UMySaveGame* LoadedGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Leaderboard"), 0));
	
	if (UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass())))
	{
		// Set data on the savegame object.
		if (LoadedGame)
		{
			SaveGameInstance->LeaderBoardEntries = LoadedGame->LeaderBoardEntries;
		}
		SaveGameInstance->LeaderBoardEntries.Add({ Name.IsEmpty() ? TEXT("(Empty)") : Name.ToString(), TimeSurvived});

		// Save the data immediately.
		if (!UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Leaderboard"), 0))
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to save a game!"));
		}
	}

	bWasSaved = true;
}