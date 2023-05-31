// Fill out your copyright notice in the Description page of Project Settings.

#include "RotationAndFloatingComponent.h"

// Sets default values for this component's properties
URotationAndFloatingComponent::URotationAndFloatingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bIsRotating = true;
}

void URotationAndFloatingComponent::SetRotating(bool bValue)
{
	bIsRotating = bValue;
}

// Called when the game starts
void URotationAndFloatingComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerActor = GetOwner();
	InitialLocation = OwnerActor->GetActorLocation();
}

// Called every frame
void URotationAndFloatingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (OwnerActor && bIsRotating)
	{
		FRotator NewRotation = OwnerActor->GetActorRotation();
		FVector NewLocation = OwnerActor->GetActorLocation();
		const float RunningTime = OwnerActor->GetGameTimeSinceCreation();
		const float DeltaHeight = FMath::Sin(RunningTime); //- FMath::Sin(RunningTime);
		NewLocation.Z = InitialLocation.Z + (DeltaHeight * FloatingAltitude);
		NewRotation.Yaw += YawValue;
		OwnerActor->SetActorLocationAndRotation(NewLocation, NewRotation);
	}
}