// Fill out your copyright notice in the Description page of Project Settings.


#include "Pets/EnemyPet.h"

#include "Characters/Trainer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"


AEnemyPet::AEnemyPet()
{
	PetDetectionZone = CreateDefaultSubobject<USphereComponent>(FName("Detection Zone"));
	PetDetectionZone->SetupAttachment(GetRootComponent());
	PetDetectionZone->InitSphereRadius(DetectionTrainerRadius);
	PetDetectionZone->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	PetDetectionZone->SetCollisionResponseToAllChannels(ECR_Ignore);
	PetDetectionZone->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Overlap);
	PetDetectionZone->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	PetDetectionZone->SetGenerateOverlapEvents(true);

	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
}

void AEnemyPet::BeginPlay()
{
	Super::BeginPlay();
	
	PetDetectionZone->OnComponentBeginOverlap.AddDynamic(this, &AEnemyPet::OnSphereOverlap);
	//PetDetectionZone->OnComponentEndOverlap.AddDynamic(this, &AEnemyPet::OnSphereEndOverlap);
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
	if (bEscape)
	{
		PetDetectionZone->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
		bEscape = false;
	}
}

void AEnemyPet::CheckPatrolTarget()
{
	if (TargetTrainer != nullptr || bInCombat) return;
	
	if (InTargetRange(PatrolTarget, PatrolRadius))
	{
		PatrolTarget = GetRandomPatrolTarget();
		if (PatrolTarget == nullptr) return;
		const float WaitTime = FMath::RandRange(PatrolMinWaitTime, PatrolMaxWaitTime);
		GetWorldTimerManager().SetTimer(PatrolTimer, this, &AEnemyPet::PatrolTimerFinished, WaitTime);
	}
}

void AEnemyPet::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFrownSweep, const FHitResult& SweepResult)
{
	if (bInCombat) return;
	if (ATrainer* Trainer = Cast<ATrainer>(OtherActor))
	{
		TargetTrainer = Trainer;
		ChaseTrainer();
	}
}

void AEnemyPet::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bInCombat) return;
	if (ATrainer* Trainer = Cast<ATrainer>(OtherActor))
	{
		if (TargetTrainer)
		{
			TargetTrainer = nullptr;
		}
	}
}

void AEnemyPet::ChaseTrainer()
{
	GetWorldTimerManager().ClearTimer(PatrolTimer);
	GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
	MoveToTarget(TargetTrainer, AcceptanceRadius);
}

void AEnemyPet::StartAttack()
{
	if (TargetAllyPet)
	{
		Attack(TargetAllyPet);
	}
}

void AEnemyPet::StartCombat()
{
	Super::StartCombat();
	GetWorldTimerManager().ClearTimer(PatrolTimer);
	GetWorldTimerManager().SetTimer(AttackCooldownTimer, this, &AEnemyPet::StartAttack, TimeToAttack);
}

void AEnemyPet::EndCombatByEscape()
{
	Super::EndCombatByEscape();
	UE_LOG(LogTemp, Warning, TEXT("EndCombatEscapeEnemyPet"));
	GetCharacterMovement()->MaxWalkSpeed = PatrolSpeed;
	MoveToTarget(PatrolTarget, AcceptanceRadius);
	TargetTrainer = nullptr;
	TargetAllyPet = nullptr;
	PetDetectionZone->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	bEscape = true;
	GetWorldTimerManager().ClearTimer(AttackCooldownTimer);
}

void AEnemyPet::EndCombatByCapture()
{
	Super::EndCombatByCapture();
	TargetTrainer = nullptr;
	TargetAllyPet = nullptr;
	GetWorldTimerManager().ClearTimer(AttackCooldownTimer);
	Destroy();
}

void AEnemyPet::AttackEnd()
{
	Super::AttackEnd();
	GetWorldTimerManager().SetTimer(AttackCooldownTimer, this, &AEnemyPet::StartAttack, TimeToAttack);
}

void AEnemyPet::SetPetTarget(ABasePet* PetTarget)
{
	if (PetTarget) TargetAllyPet = PetTarget;
}

