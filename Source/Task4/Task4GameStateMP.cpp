// Fill out your copyright notice in the Description page of Project Settings.

#include "Task4GameStateMP.h"

#include "GameSessionSubsystem.h"
#include "Kismet/GameplayStatics.h"

ATask4GameStateMP::ATask4GameStateMP()
{
	bReplicates = true;
}

void ATask4GameStateMP::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATask4GameStateMP, StartTime);
	DOREPLIFETIME(ATask4GameStateMP, bIsStarted);
}

float ATask4GameStateMP::GetRoundTime() const
{
	return GetServerWorldTimeSeconds() - StartTime;
}

void ATask4GameStateMP::RemovePlayerState(APlayerState* PlayerState)
{
	Super::RemovePlayerState(PlayerState);
	if(PlayerArray.Num() == 0)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel("Lobby");
			if (IsRunningDedicatedServer())
			{
				UGameSessionSubsystem* GameSessionSubsystem = UGameplayStatics::GetGameInstance(World)->GetSubsystem<UGameSessionSubsystem>();
				if (GameSessionSubsystem)
				{
					GameSessionSubsystem->DestroySession();
				}
			}
		}
	}
}
