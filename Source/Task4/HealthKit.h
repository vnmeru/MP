// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthKit.generated.h"
class AHealthKit;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealtHitPickUp, AHealthKit*, SpeedKit);

DECLARE_STATS_GROUP(TEXT("HealthKit"), STATGROUP_Healthkit, STATCAT_Advanced);

DECLARE_DWORD_ACCUMULATOR_STAT(TEXT("HealthKit Spawned"), STAT_ACTORSPAWN, STATGROUP_Healthkit);

DECLARE_DWORD_ACCUMULATOR_STAT(TEXT("Pickedup Num"), STAT_TIMESPICKEDUP, STATGROUP_Healthkit);

DECLARE_MEMORY_STAT(TEXT("Mesh Memory"), STAT_MESHMEMORY, STATGROUP_Healthkit);

DECLARE_CYCLE_STAT(TEXT("Overlap"), STAT_OVERLAP_CYCLE, STATGROUP_Healthkit);

UCLASS()
class TASK4_API AHealthKit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthKit();

	FHealtHitPickUp HealtKitPickUp;

	void SetVisible(bool bVisibility);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	
protected:

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere)
	class URotationAndFloatingComponent* RotationAndFloatingComponent;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionBox;

	UFUNCTION()
	void Rep_OnVisibilityChanged();

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=Rep_OnVisibilityChanged)
	bool bIsVisible = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* HealthKitModel;
};
