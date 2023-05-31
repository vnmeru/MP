// Fill out your copyright notice in the Description page of Project Settings.


#include "MapVoteMenuWidget.h"

#include "GameModeWithVoteMap.h"
#include "MyPlayerController.h"

void UMapVoteMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	NormalGameVoteButton->OnPressed.AddUniqueDynamic(this,&ThisClass::NormalGameVoted);
	ShieldGameVoteButton->OnPressed.AddUniqueDynamic(this, &ThisClass::ShieldGameVoted);
}

void UMapVoteMenuWidget::NormalGameVoted()
{
	const UWorld* World = GetWorld();
	if (World)
	{
		AMyPlayerController* MyController = Cast<AMyPlayerController>(World->GetFirstPlayerController());
		if (MyController)
		{
			MyController->Vote(VoteMap::NormalGame);
		}
	}
}

void UMapVoteMenuWidget::ShieldGameVoted()
{
	const UWorld* World = GetWorld();
	if (World)
	{
		AMyPlayerController* MyController = Cast<AMyPlayerController>(World->GetFirstPlayerController());
		if (MyController)
		{
			MyController->Vote(VoteMap::ShieldGame);
		}
	}
}

void UMapVoteMenuWidget::SetVoteTimer_Implementation(int32 Time)
{
	TimeRemeaningText->SetText(FText::AsNumber(Time));
}