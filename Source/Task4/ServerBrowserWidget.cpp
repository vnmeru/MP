// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerBrowserWidget.h"

#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "GameSessionSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Kismet/GameplayStatics.h"

void UServerBrowserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HostButton->OnPressed.AddUniqueDynamic(this, &UServerBrowserWidget::OnHostButtonPressed);
	CloseButton->OnPressed.AddUniqueDynamic(this, &ThisClass::OnCloseButtonPressed);
	RefreshButton->OnPressed.AddUniqueDynamic(this, &ThisClass::OnRefreshButtonClicked);

	const UWorld* World = GetWorld();
	if (World)
	{
		UGameSessionSubsystem* GameSession = UGameplayStatics::GetGameInstance(World)->GetSubsystem<UGameSessionSubsystem>();
		if (GameSession)
		{
			GameSession->OnFindSessionsCompleteEvent.AddUniqueDynamic(this, &ThisClass::OnSessionFound);
		}
	}
	Refresh();
}

void UServerBrowserWidget::Refresh()
{
	ServerBox->ClearChildren();
	const UWorld* World = GetWorld();
	if (World)
	{
		UGameSessionSubsystem* GameSession = UGameplayStatics::GetGameInstance(World)->GetSubsystem<UGameSessionSubsystem>();
		if (GameSession)
		{
			GameSession->FindSessions(5, true);
		}
	}
}

void UServerBrowserWidget::OnSessionFound(bool Successful)
{
	if (Successful)
	{
		UWorld* World = GetWorld();
		if (!World)
		{
			return;
		}

		UGameSessionSubsystem* GameSession = UGameplayStatics::GetGameInstance(World)->GetSubsystem<UGameSessionSubsystem>();
		if (GameSession)
		{
			FOnlineSessionSearch* SearchResult = GameSession->LastSessionSearch.Get();
			if (SearchResult)
			{
				if(LineWidget)
				{
					for (auto& Result : SearchResult->SearchResults)
					{
						UServerBrowserLineWidget* NewLine = CreateWidget<UServerBrowserLineWidget>(World, LineWidget);

						if (NewLine == nullptr)
						{
							continue;
						}

						FString FormattedString = Result.Session.OwningUserName;
						FormattedString.RemoveAt(9, FormattedString.Len() - 9);

						NewLine->SessionResult = &Result;
						NewLine->PlayersText->SetText(FText::FromString(FString::Printf(TEXT("%i/%i"), Result.Session.SessionSettings.NumPublicConnections -  Result.Session.NumOpenPublicConnections, Result.Session.SessionSettings.NumPublicConnections)));
						NewLine->ServerNameText->SetText(FText::FromString(FormattedString));

						LineWidgets.Add(NewLine);
						ServerBox->AddChildToVerticalBox(NewLine);
					}
				}
			}
		}
	}
}

void UServerBrowserWidget::OnSessionCreated(bool Success)
{

	if (Success)
	{
		const UWorld* World = GetWorld();
		if (World)
		{
			UGameplayStatics::OpenLevel(World, "Lobby", true, "listen");
		}
	}
}

void UServerBrowserWidget::OnHostButtonPressed()
{
	const UWorld* World = GetWorld();
	if (World)
	{
		UGameSessionSubsystem* GameSession = UGameplayStatics::GetGameInstance(World)->GetSubsystem<UGameSessionSubsystem>();
		if (GameSession)
		{
			GameSession->OnCreateSessionCompleteEvent.AddUniqueDynamic(this, &ThisClass::OnSessionCreated);
			GameSession->CreateSession(5, true);
		}
	}
}

void UServerBrowserWidget::OnCloseButtonPressed()
{
	SetIsEnabled(false);
	SetVisibility(ESlateVisibility::Collapsed);
}

void UServerBrowserWidget::OnRefreshButtonClicked()
{
	Refresh();
}

