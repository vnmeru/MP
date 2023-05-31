// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSessionSubsystem.h"
#include "OnlineSubsystemUtils.h"

UGameSessionSubsystem::UGameSessionSubsystem()
{
	CreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionCompleted);
	FindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionsCompleted);
	JoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionCompleted);
	DestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionCompleted);

}
void UGameSessionSubsystem::CreateSession(int32 NumConnections, bool IsLAN)
{
	const UWorld* World = GetWorld();
	if (World)
	{
		const IOnlineSessionPtr sessionInterface = Online::GetSessionInterface(World);

		if (!sessionInterface.IsValid())
		{
			OnCreateSessionCompleteEvent.Broadcast(false);
			UE_LOG(LogTemp, Display, TEXT("Failed to create a session (Interface is not valid!)"));
			return;
		}

		SessionSettings = MakeShareable(new FOnlineSessionSettings());
		SessionSettings->NumPrivateConnections = 0;
		SessionSettings->NumPublicConnections = NumConnections;
		SessionSettings->bAllowJoinInProgress = false;
		SessionSettings->bAllowInvites = true;
		SessionSettings->bIsLANMatch = true;
		SessionSettings->bShouldAdvertise = true;
		SessionSettings->bAllowJoinViaPresence = true;
		SessionSettings->bUsesPresence = false;

		SessionSettings->Set(SETTING_MAPNAME, FString("NormalGameLevel"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		CreateSessionCompleteDelegateHandle = sessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

		ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();

		bool bCreated = false;
		if (LocalPlayer)
		{
			bCreated = sessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *SessionSettings);
		}
		else
		{
			//We're running on Dedicated Server
			bCreated = sessionInterface->CreateSession(0, NAME_GameSession, *SessionSettings);
		}
		if(!bCreated)
		{
			sessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
			OnCreateSessionCompleteEvent.Broadcast(false);
			UE_LOG(LogTemp, Display, TEXT("Failed to create a session (Unknown Error!)"));
		}
	}
}

void UGameSessionSubsystem::OnCreateSessionCompleted(FName Name, bool Successful)
{
	const UWorld* World = GetWorld();
	if (World)
	{
		const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(World);
		if (SessionInterface.IsValid())
		{
			SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
			OnCreateSessionCompleteEvent.Broadcast(Successful);
		}
	}
}

void UGameSessionSubsystem::OnFindSessionsCompleted(bool Successful)
{
	const UWorld* World = GetWorld();
	if (World)
	{
		const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(World);
		if (SessionInterface.IsValid())
		{
			SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);
			OnFindSessionsCompleteEvent.Broadcast(Successful);
		}
	}
}

void UGameSessionSubsystem::JoinSession(const FOnlineSessionSearchResult& Session )
{
	const UWorld* World = GetWorld();
	if (World)
	{
		const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(World);
		if (!SessionInterface.IsValid())
		{
			OnJoinGameSessionCompleteEvent.Broadcast(false);
			UE_LOG(LogTemp, Display, TEXT("Failed to join a session (Interface is not valid!)"));
			return;
		}

		JoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);

		const ULocalPlayer* LocalPlayer = World->GetFirstLocalPlayerFromController();
		if (LocalPlayer)
		{
			if (!SessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, Session))
			{
				SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);

				OnJoinGameSessionCompleteEvent.Broadcast(false);

				UE_LOG(LogTemp, Display, TEXT("Failed to join a session (Unknown Error)"));

			}
		}
	}
}

void UGameSessionSubsystem::OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	const UWorld* World = GetWorld();
	if (World)
	{
		const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(World);
		if (SessionInterface)
		{
			SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);
		}

		OnJoinGameSessionCompleteEvent.Broadcast(Result == EOnJoinSessionCompleteResult::Success);
	}
}

bool UGameSessionSubsystem::TryTravelToCurrentSession() const
{
	const UWorld* World = GetWorld();
	if (World)
	{
		const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(World);
		if (SessionInterface.IsValid())
		{
			FString ConnectionString;
			if (SessionInterface->GetResolvedConnectString(NAME_GameSession, ConnectionString))
			{
				APlayerController* playerController = World->GetFirstPlayerController();
				playerController->ClientTravel(ConnectionString, TRAVEL_Absolute);
				return true;
			}
		}
	}
	return false;
}

void UGameSessionSubsystem::FindSessions(int32 MaxSearchResults, bool IsLANQuery)
{
	const UWorld* World = GetWorld();
	if (World)
	{
		const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(World);
		if (!SessionInterface.IsValid())
		{
			OnFindSessionsCompleteEvent.Broadcast(false);
			UE_LOG(LogTemp, Display, TEXT("Failed to find a session (Interface is not valid!)"));

			return;
		}

		FindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegate);

		LastSessionSearch = MakeShareable(new FOnlineSessionSearch());
		LastSessionSearch->MaxSearchResults = MaxSearchResults;
		LastSessionSearch->bIsLanQuery = IsLANQuery;

		const ULocalPlayer* localPlayer = World->GetFirstLocalPlayerFromController();
		if (!SessionInterface->FindSessions(*localPlayer->GetPreferredUniqueNetId(), LastSessionSearch.ToSharedRef()))
		{
			SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);

			OnFindSessionsCompleteEvent.Broadcast(false);
			UE_LOG(LogTemp, Display, TEXT("Failed to find a session (Unknown Error!)"));

		}
	}
}
void UGameSessionSubsystem::DestroySession()
{
	const UWorld* World = GetWorld();
	if (World)
	{
		const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(World);
		if (!SessionInterface.IsValid())
		{
			OnDestroySessionCompleteEvent.Broadcast(false);
			return;
		}

		DestroySessionCompleteDelegateHandle = SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegate);

		if (!SessionInterface->DestroySession(NAME_GameSession))
		{
			SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegateHandle);

			OnDestroySessionCompleteEvent.Broadcast(false);
		}
	}
}

void UGameSessionSubsystem::OnDestroySessionCompleted(FName SessionName, bool Successful)
{
	const UWorld* World = GetWorld();
	if (World)
	{
		const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(World);
		if (SessionInterface)
		{
			SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegateHandle);
		}

		OnDestroySessionCompleteEvent.Broadcast(Successful);
	}
}