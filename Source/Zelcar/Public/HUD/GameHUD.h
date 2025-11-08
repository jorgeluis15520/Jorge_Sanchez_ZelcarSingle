// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

class UTrainerWidget;

UCLASS()
class ZELCAR_API AGameHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<UTrainerWidget> TrainerWidgetClass;

	UPROPERTY()
	UTrainerWidget* TrainerWidget;

public:
	FORCEINLINE UTrainerWidget* GetTrainerWidget() { return TrainerWidget; }	
};
