// Fill out your copyright notice in the Description page of Project Settings.


#include "Task4EngineSubsystem.h"
#include "AbilitySystemGlobals.h"

void UTask4EngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UAbilitySystemGlobals::Get().InitGlobalData();
}
