// Fill out your copyright notice in the Description page of Project Settings.


#include "Pets/EnemyPet.h"
#include "GameFramework/CharacterMovementComponent.h"

void AEnemyPet::BeginPlay()
{
	Super::BeginPlay();
	
	InitializePet();
}

void AEnemyPet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CheckPatrolTarget();
}

AActor* AEnemyPet::GetRandomPatrolTarget()
{
	TArray<AActor*> FreePoints;
	for (AActor* PatrolPoint : PatrolTargets)
	{
		if (PatrolPoint != PatrolTarget)
		{
			FreePoints.AddUnique(PatrolPoint);
		}
	}

	const int32 NumFreePoints = FreePoints.Num();
	if (NumFreePoints > 0)
	{
		int32 SelectionIndex = FMath::RandRange(0, NumFreePoints - 1);
		return FreePoints[SelectionIndex];
	}

	return nullptr;
}

void AEnemyPet::InitializePet()
{
	Super::InitializePet();
	GetCharacterMovement()->MaxWalkSpeed = PatrolSpeed;
	
	if (PatrolTarget)
	{
		MoveToTarget(PatrolTarget, AcceptanceRadius);
	}
}

bool AEnemyPet::InTargetRange(AActor* Target, float RadiusRange)
{
	if (Target)
	{
		const float Distance = FVector::Dist(PatrolTarget->GetActorLocation(), GetActorLocation());
		return Distance <= RadiusRange;
	}
	
	return false;
}

void AEnemyPet::PatrolTimerFinished()
{
	MoveToTarget(PatrolTarget, AcceptanceRadius);
}

void AEnemyPet::CheckPatrolTarget()
{
	if (InTargetRange(PatrolTarget, PatrolRadius))
	{
		PatrolTarget = GetRandomPatrolTarget();
		if (PatrolTarget == nullptr) return;
		const float WaitTime = FMath::RandRange(PatrolMinWaitTime, PatrolMaxWaitTime);
		GetWorldTimerManager().SetTimer(PatrolTimer, this, &AEnemyPet::PatrolTimerFinished, WaitTime);
	}
}
