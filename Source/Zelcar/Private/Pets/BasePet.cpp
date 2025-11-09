// Fill out your copyright notice in the Description page of Project Settings.


#include "Pets/BasePet.h"
#include "AIController.h"
#include "Components/HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HUD/HealthBarWidgetComponent.h"
#include "Navigation/PathFollowingComponent.h"

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
}


