// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameSessionSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FT4OnCreateSessionComplete, bool, Succeeded);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FT4OnFindSessionsComplete, bool, Succeeded);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FT4OnJoinSessionComplete, bool, Succeeded);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FT4OnDestroySessionComplete, bool, Successful);


UCLASS()
class TASK4_API UGameSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UGameSessionSubsystem();

	void JoinSession(const FOnlineSessionSearchResult& Session);

	void FindSessions(int32 MaxSearchResults, bool IsLANQuery);

	void DestroySession();

	void CreateSession(int32 NumConnections, bool IsLAN);

	bool TryTravelToCurrentSession() const;

public:

	FT4OnJoinSessionComplete OnJoinGameSessionCompleteEvent;

	FT4OnFindSessionsComplete OnFindSessionsCompleteEvent;

	FT4OnDestroySessionComplete OnDestroySessionCompleteEvent;

	FT4OnCreateSessionComplete OnCreateSessionCompleteEvent;


protected:

	void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void OnFindSessionsCompleted(bool Successful);

	void OnDestroySessionCompleted(FName SessionName, bool Successful);

	void OnCreateSessionCompleted(FName Name, bool Successful);

private:

	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;

	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;

	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;

	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;

	FDelegateHandle JoinSessionCompleteDelegateHandle;

	FDelegateHandle FindSessionsCompleteDelegateHandle;

	FDelegateHandle DestroySessionCompleteDelegateHandle;

	FDelegateHandle CreateSessionCompleteDelegateHandle;

public:

	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;

	TSharedPtr<FOnlineSessionSettings> SessionSettings;
};
