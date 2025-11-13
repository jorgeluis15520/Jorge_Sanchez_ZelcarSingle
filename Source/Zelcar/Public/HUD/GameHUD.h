// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

class UCombatWidget;
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
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<UCombatWidget> CombatWidgetClass;

	UPROPERTY()
	UTrainerWidget* TrainerWidget;
	UPROPERTY()
	UPetInventoryWidget* PetInventoryWidget;
	UPROPERTY()
	UCombatWidget* CombatWidget;

public:
	FORCEINLINE UTrainerWidget* GetTrainerWidget() { return TrainerWidget; }	
	FORCEINLINE UPetInventoryWidget* GetPetInventoyWidget() { return PetInventoryWidget; }
	FORCEINLINE UCombatWidget* GetCombatWidget() { return CombatWidget; }

	void ShowCombatWidget();
	void HideCombatWidget();
};
