// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/HealthBarWidgetComponent.h"

#include "Components/ProgressBar.h"
#include "HUD/HealthBarWidget.h"

void UHealthBarWidgetComponent::SetHealthBarPercent(float Percentage)
{
	if (HealthBarWidget == nullptr)
	{
		HealthBarWidget = Cast<UHealthBarWidget>(GetUserWidgetObject());
	}

	if (HealthBarWidget && HealthBarWidget->HealthBar)
	{
		HealthBarWidget->HealthBar->SetPercent(Percentage);
	}
}
