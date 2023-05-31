// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerBrowserLineWidget.h"

#include "GameSessionSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UServerBrowserLineWidget::NativeConstruct()
{
	Super::NativeConstruct();

	JoinButton->OnPressed.AddUniqueDynamic(this, &ThisClass::Join);
}

void UServerBrowserLineWidget::Join()
{
	const UWorld* World = GetWorld();
	if (World)
	{
		UGameSessionSubsystem* GameSession = UGameplayStatics::GetGameInstance(World)->GetSubsystem<UGameSessionSubsystem>();
		if (GameSession)
		{
			GameSession->OnJoinGameSessionCompleteEvent.AddUniqueDynamic(this, &ThisClass::OnJoin);
			GameSession->JoinSession(*SessionResult);
		}
	}
}
void UServerBrowserLineWidget::OnJoin(bool Success)
{
	const UWorld* World = GetWorld();
	if (World)
	{
		const UGameSessionSubsystem* GameSession = UGameplayStatics::GetGameInstance(World)->GetSubsystem<UGameSessionSubsystem>();
		if (GameSession)
		{
			GameSession->TryTravelToCurrentSession();
		}
	}
}