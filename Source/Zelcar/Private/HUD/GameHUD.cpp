// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GameHUD.h"
#include "HUD/TrainerWidget.h"

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && TrainerWidgetClass)
		{
			TrainerWidget = CreateWidget<UTrainerWidget>(Controller, TrainerWidgetClass);
			TrainerWidget->AddToViewport();
		}
	}
	
}
