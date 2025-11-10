// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

class UTrainerWidget;
class UPetInventoryWidget;

UCLASS()
class ZELCAR_API AGameHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<UTrainerWidget> TrainerWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<UPetInventoryWidget> PetInventoryWidgetClass;

	UPROPERTY()
	UTrainerWidget* TrainerWidget;
	UPROPERTY()
	UPetInventoryWidget* PetInventoryWidget;

public:
	FORCEINLINE UTrainerWidget* GetTrainerWidget() { return TrainerWidget; }	
	FORCEINLINE UPetInventoryWidget* GetPetInventoyWidget() { return PetInventoryWidget; }	
};
