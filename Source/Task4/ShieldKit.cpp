// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldKit.h"
#include "Components/BoxComponent.h"
#include "RotationAndFloatingComponent.h"
#include "ShieldGameCharacter.h"

// Sets default values
AShieldKit::AShieldKit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBoxComponent"));
	if (CollisionBox != nullptr)
	{
		CollisionBox->SetBoxExtent(FVector(80.f, 80.f, 120.f));
		CollisionBox->SetCollisionProfileName("Trigger");
		RootComponent = CollisionBox;
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
	}

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	if (StaticMesh)
	{
		StaticMesh->SetStaticMesh(ShieldModel);
		StaticMesh->SetupAttachment(RootComponent);
		StaticMesh->SetCollisionProfileName("NoCollision");
	}

	RotationAndFloatingComponent = CreateDefaultSubobject<URotationAndFloatingComponent>(TEXT("RotationAndFloatingComponent"));
	
}

// Called when the game starts or when spawned
void AShieldKit::BeginPlay()
{
	Super::BeginPlay();
	DynamicMaterial = UMaterialInstanceDynamic::Create(StaticMesh->GetMaterial(0), this);
	if (DynamicMaterial)
	{
		StaticMesh->SetMaterial(0, DynamicMaterial);
	}
	UpdateColor();
}

// Called every frame
void AShieldKit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShieldKit::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AShieldGameCharacter* Character = Cast<AShieldGameCharacter>(OtherActor);
	if(Character)
	{
		Character->SetShieldType(ShieldColor);
	}
}

void AShieldKit::UpdateColor()
{
	FLinearColor Color;

	switch (ShieldColor)
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
