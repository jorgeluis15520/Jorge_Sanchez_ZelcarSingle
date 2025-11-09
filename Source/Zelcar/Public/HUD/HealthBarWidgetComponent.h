// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HealthBarWidgetComponent.generated.h"

class UHealthBarWidget;

UCLASS()
class ZELCAR_API UHealthBarWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	void SetHealthBarPercent(float Percentage);
private:
	UPROPERTY()
	UHealthBarWidget* HealthBarWidget;
};
