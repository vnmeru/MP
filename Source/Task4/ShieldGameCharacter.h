// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacterBase.h"
#include "GameFramework/Character.h"
#include "ShieldGameGameMode.h"
#include "ShieldGameCharacter.generated.h"

UCLASS()
class TASK4_API AShieldGameCharacter : public AMyCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	void SetShieldType(AttackColor Type);

	AttackColor GetShieldType();

	AShieldGameCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetShieldColor(AttackColor Color);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ShieldComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* ShieldModel;

	UPROPERTY(Transient)
	UMaterialInstanceDynamic* ShieldDynamicMaterial;

	AttackColor ShieldType = AttackColor::None;
};
