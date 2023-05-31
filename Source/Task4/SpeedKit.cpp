// Fill out your copyright notice in the Description page of Project Settings.

#include "SpeedKit.h"

#include "MyCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RotationAndFloatingComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
ASpeedKit::ASpeedKit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBoxComponent"));
	if (CollisionBox != nullptr)
	{
		CollisionBox->SetBoxExtent(FVector(80.f, 80.f, 120.f));
		CollisionBox->SetCollisionProfileName("Trigger");
		RootComponent = CollisionBox;
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASpeedKit::OnOverlapBegin);
	}

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	if (StaticMesh)
	{
		StaticMesh->SetStaticMesh(SpeedKitModel);
		StaticMesh->SetupAttachment(RootComponent);
		StaticMesh->SetCollisionProfileName("NoCollision");
	}

	RotationAndFloatingComponent = CreateDefaultSubobject<URotationAndFloatingComponent>(TEXT("RotationAndFloatingComponent"));

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextRenderComponent->SetupAttachment(GetRootComponent());
	TextRenderComponent->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
}

void ASpeedKit::OnTextTimerTick()
{
	--SecondsLeft;
	if (TextRenderComponent)
	{
		TextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%02i:%02i"), (SecondsLeft / 60) % 60, SecondsLeft % 60)));
	}
	if(SecondsLeft<=0)
	{
		GetWorldTimerManager().ClearTimer(TextTimerHandle);
	}
}

// Called when the game starts or when spawned
void ASpeedKit::BeginPlay()
{
	Super::BeginPlay();
	SetVisible(true);
}

// Called every frame
void ASpeedKit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TextRenderComponent)
	{
		TextRenderComponent->SetTextRenderColor(FColor::Cyan);
		TextRenderComponent->SetWorldSize(50);
		TextRenderComponent->SetRelativeLocation(FVector(0, 0, 100));
	}
	if (const UWorld* World = GetWorld())
	{
		if (const APlayerController* MyPlayerController = World->GetFirstPlayerController())
		{
			const APlayerCameraManager* PlayerCamera = MyPlayerController->PlayerCameraManager;
			if (PlayerCamera)
			{
				const FRotator NeedRotator = (PlayerCamera->GetActorForwardVector() * -1.0f).Rotation();
				if (TextRenderComponent)
				{
					TextRenderComponent->SetWorldRotation(NeedRotator);
				}
			}
		}
	}
}
void ASpeedKit::Enable()
{
	SetVisible(true);
}

void ASpeedKit::SetVisible(bool bVisibility)
{
	bIsVisible = bVisibility;

	StaticMesh->SetVisibility(bVisibility);

	if (TextRenderComponent)
	{
		TextRenderComponent->SetVisibility(!bVisibility);
	}
	
	RotationAndFloatingComponent->SetRotating(bVisibility);
}
void ASpeedKit::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsVisible)
	{
		AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
		if (Character)
		{
			Character->OnSpeedUp();
		}
		
		SetVisible(false);

		SecondsLeft = 15;
		if (TextRenderComponent)
		{
			TextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%02i:%02i"), (SecondsLeft / 60) % 60, SecondsLeft % 60)));
		}
		GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASpeedKit::Enable, SecondsLeft, false);
		GetWorldTimerManager().SetTimer(TextTimerHandle, this, &ASpeedKit::OnTextTimerTick, 1.f, true);
	}
}