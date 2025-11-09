// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pets/BasePet.h"
#include "EnemyPet.generated.h"

/**
 * 
 */
UCLASS()
class ZELCAR_API AEnemyPet : public ABasePet
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void InitializePet() override;
private:
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TObjectPtr<AActor> PatrolTarget;
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;
	
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float AcceptanceRadius = 50.f;
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolRadius = 150.f;
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolMinWaitTime = 6.f;
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolMaxWaitTime = 10.f;
	UPROPERTY(editAnywhere, Category = "AI Navigation")
	float PatrolSpeed = 150.f;

	FTimerHandle PatrolTimer;
	bool InTargetRange(AActor* Target, float RadiusRange);
	void PatrolTimerFinished();
	void CheckPatrolTarget();
	AActor* GetRandomPatrolTarget();
};
