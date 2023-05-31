// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "DeathScreenWidget.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

UCLASS()
class TASK4_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void UpdateHUDHealth(float Health);

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Health;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentTime;

	UPROPERTY(EditAnywhere)
	class AMyCharacter* Character;

protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
};