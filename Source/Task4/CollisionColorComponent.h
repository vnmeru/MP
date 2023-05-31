// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollisionColorComponent.generated.h"

UENUM(BlueprintType)
enum class EAttackColor : uint8 {
	Red = 0		UMETA(DisplayName = "Red"),
	Green = 1	UMETA(DisplayName = "Green"),
	Blue = 2	UMETA(DisplayName = "Blue"),
	Max = 3		UMETA(Hidden),
	None = 4	UMETA(Hidden)
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnColorChanged, EAttackColor, NewColor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TASK4_API UCollisionColorComponent : public UActorComponent
{
	GENERATED_BODY()

private:	
	// Sets default values for this component's properties
	UCollisionColorComponent();

	void ResetCollisionChannels();

public:	

	FOnColorChanged OnColorChangedEvent;

	UFUNCTION(NetMulticast,Reliable)
	void SetColor(EAttackColor NewColor);

	EAttackColor GetCurrentColor() const;

	void SetCollisionComponent(UPrimitiveComponent* Component);

	void SetIsRecierver(bool bIsRecierver);
private:

	UPROPERTY(EditAnywhere)
	UPrimitiveComponent* CollisionComponent;


	//UFUNCTION()
	//void Rep_OnColorChanged();

	//UPROPERTY(ReplicatedUsing=Rep_OnColorChanged)
	EAttackColor Color = EAttackColor::None;

	bool bIsRecierver;

	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
