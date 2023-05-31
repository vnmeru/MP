// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShieldGameGameMode.h"
#include "GameFramework/Actor.h"
#include "ShieldKit.generated.h"

UCLASS()
class TASK4_API AShieldKit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShieldKit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class URotationAndFloatingComponent* RotationAndFloatingComponent;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* ShieldModel;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMesh;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	AttackColor ShieldColor;

	UPROPERTY(Transient)
	UMaterialInstanceDynamic* DynamicMaterial;
	void UpdateColor();
};
