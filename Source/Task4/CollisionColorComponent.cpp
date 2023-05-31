// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionColorComponent.h"

#include "Net/UnrealNetwork.h"

#define ECC_Blue ECollisionChannel::ECC_GameTraceChannel1
#define ECC_Red ECollisionChannel::ECC_GameTraceChannel2
#define ECC_Green ECollisionChannel::ECC_GameTraceChannel3


UCollisionColorComponent::UCollisionColorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCollisionColorComponent::ResetCollisionChannels()
{
	if (CollisionComponent)
	{
		if (bIsRecierver)
		{
			CollisionComponent->SetCollisionResponseToChannel(ECC_Blue, ECollisionResponse::ECR_Overlap);
			CollisionComponent->SetCollisionResponseToChannel(ECC_Red, ECollisionResponse::ECR_Overlap);
			CollisionComponent->SetCollisionResponseToChannel(ECC_Green, ECollisionResponse::ECR_Overlap);
		}
	}
}

void UCollisionColorComponent::SetColor_Implementation(EAttackColor NewColor)
{
	Color = NewColor;
	ResetCollisionChannels();

	if (CollisionComponent)
	{
		switch (NewColor)
		{
		case EAttackColor::Red:
		{
			if (bIsRecierver)
			{
				CollisionComponent->SetCollisionResponseToChannel(ECC_Red, ECollisionResponse::ECR_Ignore);
			}
			else
			{
				CollisionComponent->SetCollisionProfileName(TEXT("RedProjectile"));
			}

			break;
		}
		case EAttackColor::Green:
		{
			if (bIsRecierver)
			{
				CollisionComponent->SetCollisionResponseToChannel(ECC_Green, ECollisionResponse::ECR_Ignore);
			}
			else
			{
				CollisionComponent->SetCollisionProfileName(TEXT("GreenProjectile"));
			}

			break;
		}
		case EAttackColor::Blue:
		{
			if (bIsRecierver)
			{
				CollisionComponent->SetCollisionResponseToChannel(ECC_Blue, ECollisionResponse::ECR_Ignore);
			}
			else
			{
				CollisionComponent->SetCollisionProfileName(TEXT("BlueProjectile"));
			}

			break;
		}
		}
	}

	OnColorChangedEvent.Broadcast(NewColor);
}

EAttackColor UCollisionColorComponent::GetCurrentColor() const
{
	return Color;
}

void UCollisionColorComponent::SetCollisionComponent(UPrimitiveComponent* Component)
{
	CollisionComponent = Component;
}

void UCollisionColorComponent::SetIsRecierver(bool IsRecierver)
{
	this->bIsRecierver = IsRecierver;
}
