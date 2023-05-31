// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "Task4EngineSubsystem.generated.h"

//This class is used only for initializing a GAS
UCLASS()
class TASK4_API UTask4EngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

private:
	void Initialize(FSubsystemCollectionBase& Collection) override;
};
