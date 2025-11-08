// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainerAnimInstance.h"
#include "Characters/Trainer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UTrainerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Trainer = Cast<ATrainer>(TryGetPawnOwner());
	if (Trainer)
	{
		TrainerMovementComponent = Trainer->GetCharacterMovement();
	}
}

void UTrainerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (TrainerMovementComponent)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(TrainerMovementComponent->Velocity);
		IsFalling = TrainerMovementComponent->IsFalling();
	}
}
