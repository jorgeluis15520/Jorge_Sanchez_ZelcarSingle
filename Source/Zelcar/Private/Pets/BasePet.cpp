// Fill out your copyright notice in the Description page of Project Settings.


#include "Pets/BasePet.h"
#include "AIController.h"
#include "Components/HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HUD/HealthBarWidgetComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Pets/PetDataAsset.h"
#include "Components/SkeletalMeshComponent.h"

ABasePet::ABasePet()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("HealthComponent"));
	HealthBarWidgetComponent = CreateDefaultSubobject<UHealthBarWidgetComponent>(FName("HealthBarWidgetComponent"));
	HealthBarWidgetComponent->SetupAttachment(GetRootComponent());

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}


void ABasePet::BeginPlay()
{
	Super::BeginPlay();
	
	PetAIController = Cast<AAIController>(GetController());
	InitializePet();
}

void ABasePet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePet::MoveToTarget(AActor* Target, float AcceptanceRadius)
{
	if (PetAIController == nullptr || Target == nullptr) return;

	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(AcceptanceRadius);
	PetAIController->MoveTo(MoveRequest);
}

void ABasePet::InitializePet()
{
	ApplyPetData();
}

void ABasePet::ApplyPetData()
{
	if (!PetData) return;

	USkeletalMeshComponent* MeshComponent = GetMesh();
	if (!MeshComponent) return;
	
	if (PetData->SkeletalMesh)
	{
		MeshComponent->SetSkeletalMesh(PetData->SkeletalMesh);
	}

	if (PetData->AnimationBlueprint)
	{
		MeshComponent->SetAnimInstanceClass(PetData->AnimationBlueprint);
		MeshComponent->InitAnim(true);
	}
}

void ABasePet::TakeDamage(float DamageAmount)
{
	if (HealthComponent)
	{
		HealthComponent->ReceiveDamage(DamageAmount);
		HealthBarWidgetComponent->SetHealthBarPercent(HealthComponent->GetHealthPercentage());
	}
}


