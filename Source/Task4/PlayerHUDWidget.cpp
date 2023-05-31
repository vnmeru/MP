// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHUDWidget.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"
#include "MyPlayerState.h"
#include "Task4GameStateMP.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameState.h"
#include "Kismet/GameplayStatics.h"

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AMyPlayerController* Controller = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	
	if (Controller)
	{
		Controller->OnHealthUpdatedEvent.AddDynamic(this, &UPlayerHUDWidget::UpdateHUDHealth);
	}
}

void UPlayerHUDWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
	const UWorld* World = GetWorld();
	if (World)
	{
		const AMyPlayerController* Controller = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
		if (Controller)
		{
			const ATask4GameStateMP* GameStateMP = Cast<ATask4GameStateMP>(UGameplayStatics::GetGameState(World));
			auto* PS = Controller->GetPlayerState<AMyPlayerState>();
			if (PS)
			{
				if (GameStateMP->bIsStarted && !PS->bIsDead)
				{
					CurrentTime->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), GameStateMP->GetRoundTime())));
				}
			}
			
		}
	}
}

void UPlayerHUDWidget::UpdateHUDHealth(float PlayerHealth)
{
	Health->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), PlayerHealth)));
}
