// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TASK4_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UPROPERTY(EditAnywhere);
	float MaxHealth = 100;

	UPROPERTY(EditAnywhere);
	float MinHealth = 0;

	float GetHealth() const;

	void IncreaseValue(float Amount);

private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_CurrentHealth)
	float Health = 100.f;

protected:
	UHealthComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_CurrentHealth();

	void OnHealthUpdate();
	
};
