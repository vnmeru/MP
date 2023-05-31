// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardLineWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "LeaderboardWidget.generated.h"

UCLASS()
class TASK4_API ULeaderboardWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta=(BindWidget))
	class UButton* CloseButton;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* LeaderBoardBox;

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<ULeaderboardLineWidget> LeaderBoardLineClass;

	UPROPERTY(Transient)
	TArray<ULeaderboardLineWidget*> LineWidgets;

	UPROPERTY(Transient)
	class UWidget* WidgetToFocus;
protected:

	void NativeConstruct() override;

	UFUNCTION()
	void OnClose();
};
