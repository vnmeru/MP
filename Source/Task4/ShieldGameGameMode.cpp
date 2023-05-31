// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldGameGameMode.h"

#include "EngineUtils.h"
#include "MissileSpawner.h"
#include "Task4GameStateMP.h"

void AShieldGameGameMode::BeginPlay()
{
	Super::BeginPlay();
}
bool AShieldGameGameMode::ReadyToStartMatch_Implementation()
{
	return true;
	//return !NumTravellingPlayers && GameState->GetServerWorldTimeSeconds() > 5;
}
void AShieldGameGameMode::StartMatch()
{
	Super::StartMatch();
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ThisClass::FireMissiles, 10.f, true, 0.f);
	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Cyan, TEXT("MATCH HAS BEEN STARTED!"));
	ATask4GameStateMP* GameStateMP = GetGameState<ATask4GameStateMP>();

	GameStateMP->bIsStarted = true;
	GameStateMP->StartTime = GameStateMP->GetServerWorldTimeSeconds();

	UWorld* World = GetWorld();
	//GameStateMP->SetMatchState(MatchState::InProgress);
	if (World)
	{
		for (TActorIterator<AShieldGameCharacter> ITCharacter = TActorIterator<AShieldGameCharacter>(World); ITCharacter; ++ITCharacter)
		{
			//(*ITCharacter)->StartMovement();
			//(*ITCharacter)->SetLocalName();
		}
	}
}
void AShieldGameGameMode::FireMissiles()
{

	UWorld* World = GetWorld();
	TArray<AMissileSpawner*> MissileSpawners;
	if (World)
	{
		for (TActorIterator<AMissileSpawner> ITMissileSpawner = TActorIterator<AMissileSpawner>(World); ITMissileSpawner; ++ITMissileSpawner)
		{
			MissileSpawners.Add(*ITMissileSpawner);
		}
	}
	if(MissileSpawners.Num())
	{
		AMissileSpawner* Spawner = MissileSpawners[FMath::RandRange(0, MissileSpawners.Num() - 1)];
		for (TActorIterator<AShieldGameCharacter> ITCharacter = TActorIterator<AShieldGameCharacter>(World); ITCharacter; ++ITCharacter)
		{
			Spawner->Fire(*(ITCharacter));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find missile spawners!"));
	}
}
