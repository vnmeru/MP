// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShieldGameCharacter.h"
#include "MissileSpawner.generated.h"

class AMissile;
UCLASS()
class TASK4_API AMissileSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissileSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire(AShieldGameCharacter* Character);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMissile> MissileClass;
};
