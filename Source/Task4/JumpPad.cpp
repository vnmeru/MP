// Fill out your copyright notice in the Description page of Project Settings.

#include "JumpPad.h"
#include "MyCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
AJumpPad::AJumpPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBoxComponent"));

	if (CollisionBox != nullptr)
	{
		CollisionBox->SetBoxExtent(FVector(130.f, 130.f, 20.f));
		CollisionBox->SetCollisionProfileName("Trigger");
		RootComponent = CollisionBox;
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AJumpPad::OnOverlapBegin);
	}
;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	if (StaticMesh)
	{
		StaticMesh->SetStaticMesh(JumpPadModel);
		StaticMesh->SetupAttachment(RootComponent);
		StaticMesh->SetCollisionProfileName("NoCollision");
	}
}

// Called when the game starts or when spawned
void AJumpPad::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AJumpPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJumpPad::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (Character)
	{
		Character->LaunchCharacter(FVector(0, 0, 1000),false,true);
	}
}