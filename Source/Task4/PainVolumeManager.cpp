// Fill out your copyright notice in the Description page of Project Settings.
#include "PainVolumeManager.h"

// Sets default values
APainVolumeManager::APainVolumeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void APainVolumeManager::OnTimerFired()
{
	if (PainCausingVolume != nullptr)
	{
		PainCausingVolume->DamagePerSec *= 1.1f;
	}
}

// Called when the game starts or when spawned
void APainVolumeManager::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &APainVolumeManager::OnTimerFired, 5.f, true);
}