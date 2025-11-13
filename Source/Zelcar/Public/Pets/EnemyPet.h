// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pets/BasePet.h"
#include "EnemyPet.generated.h"

class USphereComponent;
class ATrainer;
class ABasePet;

UCLASS()
class ZELCAR_API AEnemyPet : public ABasePet
{
	GENERATED_BODY()
public:
	AEnemyPet();
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

	UPROPERTY(EditAnywhere, Category = "Pet Detection")
	float DetectionTrainerRadius = 400.f;
	UPROPERTY(EditAnywhere, Category = "Pet Detection")
	USphereComponent* PetDetectionZone;
	UPROPERTY(EditAnywhere, Category = "Pet Detection")
	float ChaseSpeed = 600.f;
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFrownSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UPROPERTY()
	ATrainer* TargetTrainer;

	UPROPERTY()
	ABasePet* TargetAllyPet;
	
	void ChaseTrainer();

	bool bEscape = false;
	
	UPROPERTY(EditAnywhere)
	float TimeToAttack = 5.f;
	FTimerHandle AttackCooldownTimer;
	void StartAttack();
	
public:
	virtual void StartCombat() override;
	virtual void EndCombatByEscape() override;
	virtual void EndCombatByCapture() override;
	virtual  void AttackEnd() override;
	void SetPetTarget(ABasePet* PetTarget);
};
