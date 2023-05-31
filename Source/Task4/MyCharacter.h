// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacterBase.h"
#include "PlayerHUDWidget.h"
#include "MyCharacter.generated.h"

class UHealthComponent;

UCLASS()
class TASK4_API AMyCharacter : public AMyCharacterBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float SpeedBoostSpeed = 400;

	void OnSpeedUp();

	void OnSpeedUpEnd();

protected:
	FTimerHandle SpeedUpTimerHandle;
};