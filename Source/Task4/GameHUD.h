// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUDWidget.h"
#include "GameHUD.generated.h"

/**
 * A Game HUD with Time and Health
 */
UCLASS()
class TASK4_API AGameHUD : public AHUD
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPlayerHUDWidget> PlayerHUDWidget;

	UPROPERTY(Transient)
	UPlayerHUDWidget* PlayerHUD;

	UPROPERTY(Transient)
	UDeathScreenWidget* DeathScreen;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDeathScreenWidget> DeathScreenWidget;
private:


	virtual void BeginPlay() override;

	UFUNCTION()
	void ShowDeathScreen(float Score);
};
