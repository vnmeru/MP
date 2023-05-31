// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeWithVoteMap.h"

#include "EngineUtils.h"
#include "MyCharacterBase.h"
#include "MyPlayerController.h"
#include "MyPlayerState.h"


void AGameModeWithVoteMap::OnVoteTimerUpdate()
{
	const int32 TimeRemeaning = --VoteTimeRemeaning;
	UWorld* World = GetWorld();

	if (TimeRemeaning <= 0)
	{
		GetWorldTimerManager().ClearTimer(VoteTimerHandler);
		if (World)
		{
			TArray<VoteResult> AllVotes;

			for (TActorIterator<AMyPlayerController> ITCharacter = TActorIterator<AMyPlayerController>(World); ITCharacter; ++ITCharacter)
			{
				AMyPlayerController* Controller = (*ITCharacter);
				if (Controller)
				{
					Controller->HideVoteMenu();
					if (Controller->VotedMap != VoteMap::None)
					{
						int32 ID = AllVotes.Find(Controller->VotedMap);
						if (ID == INDEX_NONE)
						{
							AllVotes.Add(VoteResult(Controller->VotedMap));
						}
						else
						{
							++AllVotes[ID].Occurences;
						}
					}
				}
			}

			// Compute max occurences of a map
			int32 ResultCount = AllVotes.Num();
			if (!ResultCount)
			{
				NextMap = static_cast<VoteMap>(FMath::Rand() % static_cast<int8>(VoteMap::Max));
			}
			else
			{
				int32 TopOccurences = 0;

				for (int32 CurrentResultIndex = 0; CurrentResultIndex < ResultCount; ++CurrentResultIndex)
				{
					TopOccurences = FMath::Max(TopOccurences, AllVotes[CurrentResultIndex].Occurences);
				}

				TArray<VoteMap> TopResults;

				for (int32 CurrentResultIndex = 0; CurrentResultIndex < ResultCount; ++CurrentResultIndex)
				{
					if (AllVotes[CurrentResultIndex].Occurences < TopOccurences)
						continue;

					TopResults.Add(AllVotes[CurrentResultIndex].SelectedGameMode);
				}

				NextMap = TopResults[FMath::RandRange(0, TopResults.Num() - 1)];
			}
			FString NextGameModeName;
			switch (NextMap)
			{
				case VoteMap::NormalGame:
				{
					NextGameModeName = TEXT("Normal Game");
					break;
				}
				case VoteMap::ShieldGame:
				{
					NextGameModeName = TEXT("Shield Game");
					break;
				}
				default:
				{
					NextGameModeName = TEXT("Lobby");
					break;
				}
			}
			for (TActorIterator<AMyPlayerController> ITCharacter = TActorIterator<AMyPlayerController>(World); ITCharacter; ++ITCharacter)
			{
				AMyPlayerController* Controller = *ITCharacter;
				if (Controller)
				{
					Controller->HideVoteMenu();
					Controller->ShowNextMapNotification(NextGameModeName);
				}
			}
			GetWorldTimerManager().SetTimer(NextMapTimerHandler, [this, World]
				{
					switch (NextMap)
					{
						case VoteMap::NormalGame:
						{
							World->ServerTravel("NormalGameLevel");
							break;
						}
						case VoteMap::ShieldGame:
						{
							World->ServerTravel("ShieldGameLevel");
							break;
						}
						default:
						{
							World->ServerTravel("Lobby");
							break;
						}
					}
				}, VoteNotificationDelay, false);
			return;
		}
	}
	if (World)
	{
		for (TActorIterator<AMyPlayerController> ITCharacter = TActorIterator<AMyPlayerController>(World); ITCharacter; ++ITCharacter)
		{
			AMyPlayerController* Controller = *ITCharacter;
			if (Controller)
			{
				Controller->SetMapVoteTimeRemeaning(TimeRemeaning);
			}
		}
	}

}

void AGameModeWithVoteMap::EndMatch()
{
	Super::EndMatch();
	StartMapVote();
	for (TActorIterator<AMyCharacterBase> ITCharacter = TActorIterator<AMyCharacterBase>(GetWorld()); ITCharacter; ++ITCharacter)
	{
		AMyPlayerController* Controller = Cast<AMyPlayerController>((*ITCharacter)->GetController());
		if (Controller)
		{
			Controller->OnCharacterDeath.Clear();
		}
	}
}

void AGameModeWithVoteMap::StartMapVote()
{
	GetWorldTimerManager().SetTimer(VoteTimerHandler, this, &ThisClass::OnVoteTimerUpdate, 1.f, true, 0.f);
	UWorld* World = GetWorld();
	if (World)
	{
		for (TActorIterator<AMyPlayerController> ITCharacter = TActorIterator<AMyPlayerController>(World); ITCharacter; ++ITCharacter)
		{
			AMyPlayerController* MyController = Cast<AMyPlayerController>((*ITCharacter));
			if (MyController)
			{
				MyController->ShowMapVote();
			}
		}
	}
}

bool AGameModeWithVoteMap::ReadyToEndMatch_Implementation()
{
	return bAllPlayersAreDead;
}

void AGameModeWithVoteMap::StartMatch()
{
	Super::StartMatch();
	for (TActorIterator<AMyCharacterBase> ITCharacter = TActorIterator<AMyCharacterBase>(GetWorld()); ITCharacter; ++ITCharacter)
	{
		AMyPlayerController* Controller = Cast<AMyPlayerController>((*ITCharacter)->GetController());
		if (Controller)
		{
			Controller->OnCharacterDeath.AddUniqueDynamic(this, &ThisClass::OnCharacterDeath);
		}
	}
}

void AGameModeWithVoteMap::OnCharacterDeath(float Time)
{
	for (TActorIterator<AMyCharacterBase> ITCharacter = TActorIterator<AMyCharacterBase>(GetWorld()); ITCharacter; ++ITCharacter)
	{
		AMyPlayerController* Controller = Cast<AMyPlayerController>((*ITCharacter)->GetController());
		if (Controller)
		{
			auto* PS = Controller->GetPlayerState<AMyPlayerState>();
			if (PS && !PS->bIsDead)
			{
				return;
			}
		}
	}
	bAllPlayersAreDead = true;
}
