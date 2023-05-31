// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"

#include "AbilitySystemComponent.h"
#include "MyCharacterBase.h"
#include "MyPlayerController.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

AMyPlayerState::AMyPlayerState()
{
	bUseCustomPlayerNames = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilityComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
}

void AMyPlayerState::OnRepMovementChanged()
{
	AMyPlayerController* Controller = Cast<AMyPlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	Controller->OnGameStartEvent.Broadcast();
}

void AMyPlayerState::OnDeathStateChanged()
{
	//if (bIsDead)
	//{
	//	auto* Character = Cast<AMyCharacterBase>(GetOwner());
	//	Character->Die();
	//}
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, bCanMove);
	DOREPLIFETIME(ThisClass, bIsDead);
}
