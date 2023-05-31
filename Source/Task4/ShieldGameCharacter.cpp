// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldGameCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AShieldGameCharacter::AShieldGameCharacter()
{
	ShieldComponent = CreateDefaultSubobject<UStaticMeshComponent>("Shield Mesh");
	if (ShieldComponent != nullptr)
	{
		ShieldComponent->SetStaticMesh(ShieldModel);
		ShieldComponent->SetupAttachment(GetMesh());
		ShieldComponent->SetCollisionProfileName("NoCollision");
	}
}

// Called when the game starts or when spawned
void AShieldGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	ShieldDynamicMaterial = UMaterialInstanceDynamic::Create(ShieldComponent->GetMaterial(0), this);
	ShieldComponent->SetMaterial(0, ShieldDynamicMaterial);

	AMyPlayerController* MyController = Cast<AMyPlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (MyController)
	{
		MyController->OnHealthUpdatedEvent.Broadcast(Health->GetHealth());
	}

	ShieldComponent->SetVisibility(false);
}

void AShieldGameCharacter::SetShieldColor(AttackColor ColorToSet)
{
	FLinearColor Color;

	switch (ColorToSet)
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
	if (ShieldDynamicMaterial)
	{
		ShieldDynamicMaterial->SetVectorParameterValue("Color", Color);
	}
}

void AShieldGameCharacter::SetShieldType(AttackColor Type)
{
	if(ShieldType == AttackColor::None)
	{
		ShieldComponent->SetVisibility(true);
	}
	SetShieldColor(Type);
	ShieldType = Type;
}

AttackColor AShieldGameCharacter::GetShieldType()
{
	return ShieldType;
}
