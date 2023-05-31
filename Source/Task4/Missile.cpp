// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile.h"

#include "EngineUtils.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMissile::AMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBoxComponent"));
	if (CollisionBox != nullptr)
	{
		RootComponent = CollisionBox;
		CollisionBox->SetGenerateOverlapEvents(true);
		CollisionBox->SetBoxExtent(FVector(175.f, 55.f, 55.f));
		//CollisionBox->SetCollisionProfileName("Trigger");
		CollisionBox->OnComponentHit.AddDynamic(this, &AMissile::OnHit);
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);

	}
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("RoketMesh");
	if (MeshComponent != nullptr)
	{
		//MeshComponent->SetStaticMesh(MissileModel);
		MeshComponent->SetupAttachment(RootComponent);
		MeshComponent->SetCollisionProfileName("NoCollision");
	}
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
   	ProjectileMovement->UpdatedComponent = RootComponent;
	
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.f;

}

void AMissile::UpdateColor()
{
	
	FLinearColor Color;
	switch(MissileType)
	{
		case AttackColor::Red:
		{
			Color = FLinearColor::Red;
			break;
		}
		case AttackColor::Green:
		{
			Color = FLinearColor::Green;
			break;
		}
		case AttackColor::Blue:
		{
			Color = FLinearColor::Blue;
			break;
		}
	}
	if (DynamicMaterial)
	{
		DynamicMaterial->SetVectorParameterValue("Color", Color);
	}
}
void AMissile::SetRandomColor()
{
	AttackColor OldColor = MissileType;
	while(true)
	{
		MissileType = static_cast<AttackColor>(FMath::Rand() % static_cast<int8>(AttackColor::Max));
		if(MissileType != OldColor)
		{
			break;
		}
	}
	UpdateColor();
}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();

	//CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMissile::OnOverlapBegin);
	if (MeshComponent)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(MeshComponent->GetMaterial(0), this);

		MeshComponent->SetMaterial(0, DynamicMaterial);
	}
	GetWorldTimerManager().SetTimer(ChangeColorTimer, this, &ThisClass::SetRandomColor, 5.f, true, 0.f);
}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!Target)
	{
		return;
	}

	const float FastSavedRate = 1.0f - FastTurnRate;
	const float SlowSavedRate = 1.0f - SlowTurnRate;

	const FVector MissilePos = GetActorLocation();
	const FVector TargetPos = Target->GetActorLocation();

	const FVector MissileDirection = GetActorForwardVector();
	FVector DesiredDirection = TargetPos - MissilePos;

	const float DistanceToTarget = DesiredDirection.Size();
	DesiredDirection.Normalize();

	float DesiredTurnRate = FastTurnRate;
	float DesiredSavedRate = FastSavedRate;
	const bool bAdjustZRate = MissilePos.Z < TargetPos.Z;

	if (DistanceToTarget < SlowRateDistanceLock && !bHasEnteredSlowLock)
	{
		bHasEnteredSlowLock = true;
	}
	else if (DistanceToTarget > SlowRateDistanceRelease && bHasEnteredSlowLock)
	{
		bHasEnteredSlowLock = false;
	}

	if (bHasEnteredSlowLock )
	{
		DesiredTurnRate = SlowTurnRate;
		DesiredSavedRate = SlowSavedRate;
	}

	FVector FinalDirection;// = DesiredDirection * DesiredTurnRate + MissileDirection * DesiredSavedRate;

	if (bAdjustZRate)
	{
		FinalDirection = FVector(
			DesiredDirection.X * DesiredTurnRate + MissileDirection.X * DesiredSavedRate,
			DesiredDirection.Y * DesiredTurnRate + MissileDirection.Y * DesiredSavedRate,
			DesiredDirection.Z * FastTurnRateZ + MissileDirection.Z * (1 - FastTurnRateZ));
	}
	else
	{
		FinalDirection = DesiredDirection * DesiredTurnRate + MissileDirection * DesiredSavedRate;
	}

	ProjectileMovement->Velocity = (FinalDirection * MissileSpeed);
	ProjectileMovement->UpdateComponentVelocity();
}

void AMissile::SetTarget(AShieldGameCharacter* Character)
{
	if (Character)
	{
		Target = Character;
	}
}

void AMissile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("OnOverlap"));
	if (!bCanDealDamage)
	{
		return;
	}
	if(OtherActor && OtherActor != this && OtherActor == Target)
	{
		AShieldGameCharacter* Character = Cast<AShieldGameCharacter>(OtherActor);
		if(Character)
		{
			if (Character->GetShieldType() != this->MissileType)
			{
				Character->TakeDamage(10.f, FDamageEvent{}, GetInstigatorController(), this);
			}
			bCanDealDamage = false;
			GetWorldTimerManager().SetTimer(StopDamageTimer, [this] { bCanDealDamage = true; }, 5.f, false);
		}
	}
}

void AMissile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}