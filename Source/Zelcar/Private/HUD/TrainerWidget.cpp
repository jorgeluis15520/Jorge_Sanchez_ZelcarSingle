// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/TrainerWidget.h"

#include "Components/ProgressBar.h"

void UTrainerWidget::SetHealthBar(float Percent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(Percent);
	}
}

void UTrainerWidget::SetStaminaBar(float Percent)
{
	if (StaminaBar)
	{
		StaminaBar->SetPercent(Percent);
	}
}
