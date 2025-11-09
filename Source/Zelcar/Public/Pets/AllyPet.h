// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pets/BasePet.h"
#include "AllyPet.generated.h"

/**
 * 
 */
UCLASS()
class ZELCAR_API AAllyPet : public ABasePet
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(visibleAnywhere)
	AActor* Trainer;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float FollowDistance = 250.f;
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float AcceptanceRadius = 100.f;

	FTimerHandle FollowTimer;
	void FollowTrainer();
};
