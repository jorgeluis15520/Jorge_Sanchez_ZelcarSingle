// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GameHUD.h"
#include "HUD/TrainerWidget.h"
#include "PetInventory/PetInventoryWidget.h"

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
				TrainerWidget->AddToViewport();
			}

			if (PetInventoryWidgetClass)
			{
				PetInventoryWidget = CreateWidget<UPetInventoryWidget>(Controller, PetInventoryWidgetClass);
				PetInventoryWidget->AddToViewport();
				PetInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
	
}
