// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GameHUD.h"
#include "HUD/TrainerWidget.h"
#include "PetInventory/PetInventoryWidget.h"
#include "HUD/CombatWidget.h"

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller)
		{
			if (TrainerWidgetClass)
			{
				TrainerWidget = CreateWidget<UTrainerWidget>(Controller, TrainerWidgetClass);
				TrainerWidget->AddToViewport(0);
			}

			if (PetInventoryWidgetClass)
			{
				PetInventoryWidget = CreateWidget<UPetInventoryWidget>(Controller, PetInventoryWidgetClass);
				PetInventoryWidget->AddToViewport(2);
				PetInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
			}

			if (CombatWidgetClass)
			{
				CombatWidget = CreateWidget<UCombatWidget>(Controller, CombatWidgetClass);
				CombatWidget->AddToViewport(1);
				CombatWidget->HideFeedBackOverlay();
				CombatWidget->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
	
}

void AGameHUD::ShowCombatWidget()
{
	if (CombatWidget)
	{
		CombatWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AGameHUD::HideCombatWidget()
{
	if (CombatWidget)
	{
		CombatWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}
