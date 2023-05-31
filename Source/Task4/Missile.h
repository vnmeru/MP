// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShieldGameCharacter.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Missile.generated.h"

UCLASS()
class TASK4_API AMissile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissile();

protected:
	void UpdateColor();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetTarget(AShieldGameCharacter* Character);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* MissileModel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(Transient)
	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionBox;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	AttackColor MissileType;

	UPROPERTY(Transient)
	AActor* Target;

	UPROPERTY(VisibleAnywhere)
	bool bHasEnteredSlowLock = false;

	UPROPERTY(EditAnywhere)
	float SlowRateDistanceLock = 5.0f * 100.0f; // 5 meters

	UPROPERTY(EditAnywhere)
	float SlowRateDistanceRelease = 20.0f * 100.0f; // 20 meters

	UPROPERTY(EditAnywhere)
	float MissileSpeed = 1000.f;

	UPROPERTY(EditAnywhere)
	float FastTurnRate = 0.075f;

	UPROPERTY(EditAnywhere)
	float SlowTurnRate = 0.01f;

	UPROPERTY(EditAnywhere)
	float FastTurnRateZ = 0.2f;

	FTimerHandle ChangeColorTimer;

	FTimerHandle StopDamageTimer;

	bool bCanDealDamage = true;

	UFUNCTION()
	void SetRandomColor();
};
