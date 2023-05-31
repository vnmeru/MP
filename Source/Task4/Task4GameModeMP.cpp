// Fill out your copyright notice in the Description page of Project Settings.


#include "Task4GameModeMP.h"

#include "EngineUtils.h"
#include "MyCharacter.h"
#include "Task4GameStateMP.h"
#include "GameFramework/GameStateBase.h"

ATask4GameModeMP::ATask4GameModeMP()
{
	//bDelayedStart = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ATask4GameModeMP::BeginPlay()
{
	Super::BeginPlay();

	TArray<AHealthKit*> HealthKits = GetAllHealthKits();

	if (HealthKits.Num() == 0)
	{
		return;
	}

	HealthKits[FMath::RandRange(0, HealthKits.Num() - 1)]->SetVisible(true);

	for (AHealthKit* HealthKit : HealthKits)
	{
		HealthKit->HealtKitPickUp.AddDynamic(this, &ATask4GameModeMP::OnHealthKitCollision);
	}
	
}

void ATask4GameModeMP::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
 
TArray<AHealthKit*> ATask4GameModeMP::GetAllHealthKits()
{
	TArray<AHealthKit*> HealthKits;

	UWorld* World = GetWorld();

	if (World)
	{
		for (TActorIterator<AHealthKit> ITHealthKit = TActorIterator<AHealthKit>(World); ITHealthKit; ++ITHealthKit)
		{
			HealthKits.Add(*ITHealthKit);
		}
	}

	return HealthKits;
}

bool ATask4GameModeMP::ReadyToStartMatch_Implementation()
{
	return true;
	//return !NumTravellingPlayers && GameState->GetServerWorldTimeSeconds() > 5;
}

void ATask4GameModeMP::StartMatch()
{
	Super::StartMatch();
	
	//GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Cyan, TEXT("MATCH HAS BEEN STARTED!"));
	ATask4GameStateMP* GameStateMP = GetGameState<ATask4GameStateMP>();

	GameStateMP->bIsStarted = true;
	GameStateMP->StartTime = GameStateMP->GetServerWorldTimeSeconds();

	UWorld* World = GetWorld();
	//GameStateMP->SetMatchState(MatchState::InProgress);
	if (World)
	{
		for (TActorIterator<AMyCharacter> ITCharacter = TActorIterator<AMyCharacter>(World); ITCharacter; ++ITCharacter)
		{
			(*ITCharacter)->StartMovement();
			(*ITCharacter)->SetLocalName();
		}
	}
}

void ATask4GameModeMP::OnHealthKitCollision(AHealthKit* HealthKit)
{
	TArray<AHealthKit*> HealthKits = GetAllHealthKits();

	if (HealthKits.Num() <= 1)
	{
		UE_LOG(LogTemp, Error, TEXT("Not enough first aid kits on the map! Aborting!"));
		return;
	}

	HealthKit->SetVisible(false);

	AHealthKit* NewHealthKit;

	while (true)
	{
		NewHealthKit = HealthKits[FMath::RandRange(0, HealthKits.Num() - 1)];
		if (NewHealthKit != HealthKit)
		{
			break;
		}
	}

	NewHealthKit->SetVisible(true);
}
