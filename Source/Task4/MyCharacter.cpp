// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void AMyCharacter::OnSpeedUp()
{
	if(SpeedUpTimerHandle.IsValid())
	{
		return;
	}

	GetWorldTimerManager().SetTimer(SpeedUpTimerHandle, this, &AMyCharacter::OnSpeedUpEnd, 5.f, false);

	GetCharacterMovement()->MaxWalkSpeed += SpeedBoostSpeed;

	UE_LOG(LogMyCharacter, Display, TEXT("Speeding Up! Current speed = %f"), GetCharacterMovement()->MaxWalkSpeed);
}

void AMyCharacter::OnSpeedUpEnd()
{
	GetCharacterMovement()->MaxWalkSpeed -= SpeedBoostSpeed;

	UE_LOG(LogMyCharacter, Display, TEXT("Disabling SpeedUp boost. Current Speed = %f"), GetCharacterMovement()->MaxWalkSpeed);
}