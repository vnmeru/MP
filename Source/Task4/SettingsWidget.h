// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsWidget.generated.h"
/**
 * 
 */
UCLASS()
class TASK4_API USettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* SaveButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* NameTextBox;

private:
	UFUNCTION()
	void Save();

	UFUNCTION()
	void OnClose();

	virtual void NativeConstruct() override;
};