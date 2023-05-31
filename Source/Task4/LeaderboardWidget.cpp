// Fill out your copyright notice in the Description page of Project Settings.

#include "LeaderboardWidget.h"
#include "LeaderboardLineWidget.h"
#include "MySaveGame.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void ULeaderboardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton->OnClicked.AddUniqueDynamic(this, &ULeaderboardWidget::OnClose);

	//Populate Leaderboard
	if (LeaderBoardLineClass != nullptr)
	{
		UMySaveGame* LoadedGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Leaderboard"), 0));
		if (LoadedGame != nullptr)
		{
			TArray<FLeaderBoardEntry>& LeaderBoardEntries = LoadedGame->LeaderBoardEntries;

			LeaderBoardEntries.Sort([](const FLeaderBoardEntry LHS, const FLeaderBoardEntry RHS) { return LHS.Score > RHS.Score; });

			const uint32 MaxElementsInLeaderboard = 5;
			const uint32 LeaderboardElements = LeaderBoardEntries.Num();

			UWorld* World = GetWorld();
			if(World == nullptr)
			{
				return;
			}

			for (uint32 DisplayElementIndex = 0; DisplayElementIndex < MaxElementsInLeaderboard; ++DisplayElementIndex)
			{
				ULeaderboardLineWidget* LineWidget = CreateWidget<ULeaderboardLineWidget>(World, LeaderBoardLineClass);

				if (LineWidget == nullptr)
				{
					continue;
				}

				LineWidgets.Add(LineWidget);

				if (DisplayElementIndex < LeaderboardElements)
				{
					FLeaderBoardEntry& LeaderBoardEntry = LeaderBoardEntries[DisplayElementIndex];
					LineWidget->NameBlock->SetText(FText::FromString(LeaderBoardEntry.PlayerName));
					LineWidget->ScoreBlock->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), LeaderBoardEntry.Score)));
				}
				else
				{
					LineWidget->NameBlock->SetText(FText::FromString(TEXT("-")));
					LineWidget->ScoreBlock->SetText(FText::AsNumber(0));
				}

				LeaderBoardBox->AddChildToVerticalBox(LineWidget);
			}
		}
	}
}

void ULeaderboardWidget::OnClose()
{
	SetIsEnabled(false);
	SetVisibility(ESlateVisibility::Collapsed);

	if (WidgetToFocus)
	{
		WidgetToFocus->SetFocus();
	}
}