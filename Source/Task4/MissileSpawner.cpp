// Fill out your copyright notice in the Description page of Project Settings.


#include "MissileSpawner.h"

#include "Missile.h"

// Sets default values
AMissileSpawner::AMissileSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMissileSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMissileSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMissileSpawner::Fire(AShieldGameCharacter* Character)
{
	FActorSpawnParameters SpawnInfo;
	AMissile* Missile = GetWorld()->SpawnActor<AMissile>(MissileClass, GetActorLocation(), GetActorRotation(), SpawnInfo);
	if (Missile)
	{
		Missile->SetTarget(Character);
	}
}