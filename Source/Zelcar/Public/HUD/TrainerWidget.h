// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TrainerWidget.generated.h"

/**
 * 
 */
UCLASS()
class ZELCAR_API UTrainerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* StaminaBar;

	void SetHealthBar(float Percent);
	void SetStaminaBar(float Percent);
};
