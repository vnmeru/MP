// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthKit.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "MyCharacterBase.h"
#include "RotationAndFloatingComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AHealthKit::AHealthKit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBoxComponent"));
	if (CollisionBox != nullptr)
	{
		CollisionBox->SetBoxExtent(FVector(110.f, 50.f, 110.f));
		CollisionBox->SetCollisionProfileName("Trigger");
		RootComponent = CollisionBox;
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AHealthKit::OnOverlapBegin);
	}
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	if (StaticMesh != nullptr)
	{
		StaticMesh->SetStaticMesh(HealthKitModel);
		StaticMesh->SetupAttachment(RootComponent);
		StaticMesh->SetCollisionProfileName("NoCollision");
	}
	RotationAndFloatingComponent = CreateDefaultSubobject<URotationAndFloatingComponent>(TEXT("RotationAndFloatingComponent"));
	SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));

	bReplicates = true;
}

// Called when the game starts or when spawned
void AHealthKit::BeginPlay()
{
	Super::BeginPlay();

	INC_DWORD_STAT(STAT_ACTORSPAWN);
	INC_MEMORY_STAT_BY(STAT_MESHMEMORY, sizeof(*this) + StaticMesh->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal));
	
	SetActorHiddenInGame(!bIsVisible);
}

void AHealthKit::SetVisible(bool bVisibility)
{
	bIsVisible = bVisibility;

	SetActorHiddenInGame(!bVisibility);

	SetActorTickEnabled(bVisibility);
}

// Called every frame
void AHealthKit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHealthKit::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SCOPE_CYCLE_COUNTER(STAT_OVERLAP_CYCLE);

	if (bIsVisible)
	{
		const AMyCharacterBase* Character = Cast<AMyCharacterBase>(OtherActor);
		if(Character)
		{
			Character->Health->IncreaseValue(5);
			HealtKitPickUp.Broadcast(this);
			INC_DWORD_STAT(STAT_TIMESPICKEDUP);
		}
	}
}

void AHealthKit::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHealthKit, bIsVisible);
}

void AHealthKit::Rep_OnVisibilityChanged()
{
	SetVisible(bIsVisible);
}
