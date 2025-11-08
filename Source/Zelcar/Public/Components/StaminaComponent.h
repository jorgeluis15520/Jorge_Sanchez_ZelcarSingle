// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZELCAR_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStaminaComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void RegenStamina(float DeltaTime);
	void LoseStamina(float DeltaTime);
	
protected:
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditAnywhere, Category = "Attributes")
	float Stamina = 100.f;
	UPROPERTY(EditAnywhere, Category = "Attributes")
	float StaminaRegenRate = 1.f;
	UPROPERTY(EditAnywhere, Category = "Attributes")
	float StaminaLoseRate = 1.f;
	UPROPERTY(VisibleAnywhere, Category = "Attributes")
	float CurrentStamina;

	float MaxStamina;

public:
	float GetStaminaPercentage();
};
