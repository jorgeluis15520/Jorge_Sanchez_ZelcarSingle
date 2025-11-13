// Fill out your copyright notice in the Description page of Project Settings.


#include "Pets/AllyPet.h"

void AAllyPet::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		Trainer = PlayerController->GetPawn();
	}

	GetWorldTimerManager().SetTimer(FollowTimer, this, &AAllyPet::FollowTrainer, 0.5f, true);
}

void AAllyPet::FollowTrainer()
{
	if (Trainer == nullptr || PetAIController == nullptr) return;
	if (bInCombat) return;
	
	const float Distance = FVector::Dist(GetActorLocation(), Trainer->GetActorLocation());
	if (Distance > FollowDistance)
	{
		MoveToTarget(Trainer, AcceptanceRadius);
	}
}

void AAllyPet::StartCombat()
{
	Super::StartCombat();

	GetWorldTimerManager().ClearTimer(FollowTimer);
}

void AAllyPet::EndCombatByEscape()
{
	Super::EndCombatByEscape();
	GetWorldTimerManager().SetTimer(FollowTimer, this, &AAllyPet::FollowTrainer, 0.5f, true);
}

void AAllyPet::EndCombatByCapture()
{
	Super::EndCombatByCapture();
	GetWorldTimerManager().SetTimer(FollowTimer, this, &AAllyPet::FollowTrainer, 0.5f, true);
}
