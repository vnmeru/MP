// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RotationAndFloatingComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TASK4_API URotationAndFloatingComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetRotating(bool bValue);
		
	UPROPERTY(EditAnywhere)
	float YawValue = 0.5f;

	UPROPERTY(EditAnywhere)
	float FloatingAltitude = 30.f;

	UPROPERTY(VisibleAnywhere)
	bool bIsRotating;
	
protected:
	// Sets default values for this component's properties
	URotationAndFloatingComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(Transient)
	FVector InitialLocation;

	UPROPERTY(Transient)
	AActor* OwnerActor;
};
