// Fill out your copyright notice in the Description page of Project Settings.


#include "Pets/BasePet.h"
#include "AIController.h"
#include "Components/HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HUD/HealthBarWidgetComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Pets/PetDataAsset.h"
#include "Components/SkeletalMeshComponent.h"
#include "AbilitiesSystem/PetAbilitySystemComponent.h"
#include "Animation/AnimMontage.h"

ABasePet::ABasePet()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("HealthComponent"));
	HealthBarWidgetComponent = CreateDefaultSubobject<UHealthBarWidgetComponent>(FName("HealthBarWidgetComponent"));
	HealthBarWidgetComponent->SetupAttachment(GetRootComponent());
	PetAbilitySystemComponent = CreateDefaultSubobject<UPetAbilitySystemComponent>(FName("PetAbilitySystem Component"));
	
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
	HideHealthBar();
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
	}

	if (PetData->BasicAttackMontage)
	{
		AttackMontage = PetData->BasicAttackMontage;
	}
}

void ABasePet::ApplyDamage(float DamageAmount)
{
	if (HealthComponent)
	{
		HealthComponent->ReceiveDamage(DamageAmount);
		HealthBarWidgetComponent->SetHealthBarPercent(HealthComponent->GetHealthPercentage());
	}
}

UAbilitySystemComponent* ABasePet::GetAbilitySystemComponent() const
{
	return PetAbilitySystemComponent;
}

void ABasePet::Attack(ABasePet* PetTarget)
{
	if (PetState != ECharacterState::ECS_Unoccupied) return;
	
	PetState = ECharacterState::ECS_Occupied;
	if (AttackMontage)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance) AnimInstance->Montage_Play(AttackMontage);
	}
	
	if (PetTarget)
	{
		PetEnemyTarget = PetTarget;
	}
}

void ABasePet::AttackEnd()
{
	if (PetEnemyTarget)
	{
		PetEnemyTarget->ApplyDamage(10.f);
		PetEnemyTarget = nullptr;
	}
	PetState = ECharacterState::ECS_Unoccupied;
}

void ABasePet::ShowHealthBar()
{
	if (HealthBarWidgetComponent)
	{
		HealthBarWidgetComponent->SetVisibility(true);
	}
}

void ABasePet::HideHealthBar()
{
	if (HealthBarWidgetComponent)
	{
		HealthBarWidgetComponent->SetVisibility(false);
	}
}

void ABasePet::StartCombat()
{
	bInCombat = true;
	PetAIController->StopMovement();
	ShowHealthBar();
}

void ABasePet::EndCombatByEscape()
{
	bInCombat = false;
	HideHealthBar();
}

void ABasePet::EndCombatByCapture()
{
	bInCombat = false;
	HideHealthBar();
}
