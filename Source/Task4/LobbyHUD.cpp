// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyHUD.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void ALobbyHUD::BeginPlay()
{
	Super::BeginPlay();
	if (LobbyWidget)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			Lobby = CreateWidget<UMultiplayerLobbyWidget>(World, LobbyWidget);
			APlayerController* MyController = World->GetFirstPlayerController();
			if (MyController)
			{
				if (!MyController->HasAuthority())
				{
					Lobby->CloseServerText->SetText(FText::FromString(TEXT("Leave Server")));
				}
				Lobby->AddToViewport();
			}
		}
	}
}
