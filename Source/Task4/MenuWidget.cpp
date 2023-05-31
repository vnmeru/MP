// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "LeaderboardWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton->OnPressed.AddUniqueDynamic(this, &UMenuWidget::OnCloseButtonClicked);
	LeaderboardButton->OnPressed.AddUniqueDynamic(this, &UMenuWidget::OnLeaderboardButtonClicked);
	MultiplayerButton->OnPressed.AddUniqueDynamic(this, &UMenuWidget::OnMultiplayerButtonClicked);
	SettingsButton->OnPressed.AddUniqueDynamic(this, &UMenuWidget::OnSettingsButtonClicked);
	StartButton->OnPressed.AddUniqueDynamic(this, &UMenuWidget::OnStartButtonClicked);

	const UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* MyController = World->GetFirstPlayerController();
		if (MyController)
		{
			MyController->bShowMouseCursor = true;
			MyController->bEnableClickEvents = true;
			MyController->bEnableMouseOverEvents = true;
			MyController->SetInputMode(FInputModeUIOnly{});
			StartButton->SetUserFocus(MyController);
		}
	}
}

void UMenuWidget::OnStartButtonClicked()
{
	const UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, "NormalGameLevel");
	}
}

void UMenuWidget::OnCloseButtonClicked()
{
	const UWorld* World = GetWorld();
	if (World)
	{
		UKismetSystemLibrary::QuitGame(World, nullptr, EQuitPreference::Quit, false);
	}
}

void UMenuWidget::OnMultiplayerButtonClicked()
{
	if (ServerBrowser)
	{
		if (ServerBrowserWidget == nullptr)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				ServerBrowserWidget = CreateWidget<UServerBrowserWidget>(World, ServerBrowser);

				if (ServerBrowserWidget != nullptr)
				{
					ServerBrowserWidget->AddToViewport();
				}
			}
		}
		else
		{
			//ServerBrowserWidget->SetIsEnabled(true);
			ServerBrowserWidget->SetVisibility(ESlateVisibility::Visible);
			ServerBrowserWidget->Refresh();
		}
	}
}

void UMenuWidget::OnSettingsButtonClicked()
{
	if (Settings)
	{
		if (SettingsWidget == nullptr)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				SettingsWidget = CreateWidget<USettingsWidget>(GetWorld(), Settings);

				if (SettingsWidget != nullptr)
				{
					SettingsWidget->AddToViewport();
				}
			}
		}
		else
		{
			SettingsWidget->SetIsEnabled(true);
			SettingsWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UMenuWidget::OnLeaderboardButtonClicked()
{
	if (LeaderBoard)
	{
		if (LeaderboardWidget == nullptr)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				LeaderboardWidget = CreateWidget<ULeaderboardWidget>(World, LeaderBoard);

				if (LeaderboardWidget != nullptr)
				{
					LeaderboardWidget->WidgetToFocus = StartButton;
					LeaderboardWidget->AddToViewport();
				}
			}
		}
		else
		{
			LeaderboardWidget->SetIsEnabled(true);
			LeaderboardWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
