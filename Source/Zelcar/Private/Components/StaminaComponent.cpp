// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StaminaComponent.h"

// Sets default values for this component's properties
UStaminaComponent::UStaminaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();
	
	MaxStamina = Stamina;
	CurrentStamina = MaxStamina;
}

void UStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UStaminaComponent::GetStaminaPercentage()
{
	return CurrentStamina / MaxStamina;
}

void UStaminaComponent::RegenStamina(float DeltaTime)
{
	CurrentStamina = FMath::Clamp(CurrentStamina + (StaminaRegenRate * DeltaTime), 0, MaxStamina);
}

void UStaminaComponent::LoseStamina(float DeltaTime)
{
	CurrentStamina = FMath::Clamp(CurrentStamina - (StaminaLoseRate * DeltaTime), 0, MaxStamina);
}
