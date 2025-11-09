// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasePet.generated.h"

class UHealthBarWidgetComponent;
class AAIController;
class UHealthComponent;
UCLASS()
class ZELCAR_API ABasePet : public ACharacter
{
	GENERATED_BODY()

public:
	ABasePet();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void MoveToTarget(AActor* Target, float AcceptanceRadius);
	virtual void InitializePet();
	
	UPROPERTY(VisibleAnywhere)
	UHealthComponent* HealthComponent;
	UPROPERTY(visibleAnywhere)
	UHealthBarWidgetComponent* HealthBarWidgetComponent;
	UPROPERTY()
	AAIController* PetAIController;

};
