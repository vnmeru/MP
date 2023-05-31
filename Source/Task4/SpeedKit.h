// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeedKit.generated.h"

UCLASS()
class TASK4_API ASpeedKit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	void SetVisible(bool bVisibility);

	void Enable();
protected:

	ASpeedKit();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:

	void OnTextTimerTick();
public:

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere)
	class UTextRenderComponent* TextRenderComponent;

	UPROPERTY(VisibleAnywhere)
	class URotationAndFloatingComponent* RotationAndFloatingComponent;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* SpeedKitModel;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UPROPERTY(Transient)
	FTimerHandle RespawnTimerHandle;

	UPROPERTY(Transient)
	FTimerHandle TextTimerHandle;

	int32 SecondsLeft;
	bool bIsVisible = true;
};