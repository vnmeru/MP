// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHUD.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"
#include "Task4GameStateMP.h"
#include "Kismet/GameplayStatics.h"


void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		AMyPlayerController* Controller = Cast<AMyPlayerController>(GetOwningPlayerController());
		if (Controller != nullptr)
		{
			Controller->OnCharacterDeath.AddDynamic(this, &AGameHUD::ShowDeathScreen);
		}

		if (PlayerHUDWidget != nullptr)
		{
			PlayerHUD = CreateWidget<UPlayerHUDWidget>(World, PlayerHUDWidget);

			if (PlayerHUD != nullptr)
			{
				PlayerHUD->AddToViewport();
			}
		}
		
	}
}

void AGameHUD::ShowDeathScreen(float TimeSurvived)
{
	UWorld* World = GetWorld();
	if (World)
	{
		if (DeathScreen == nullptr)
		{
			DeathScreen = CreateWidget<UDeathScreenWidget>(World, DeathScreenWidget);
		}
		if (DeathScreen != nullptr)
		{
			DeathScreen->SetTimeSurvived(TimeSurvived);
			DeathScreen->AddToViewport();
		}
	}
}