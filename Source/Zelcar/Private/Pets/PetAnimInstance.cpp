// Fill out your copyright notice in the Description page of Project Settings.


#include "Pets/PetAnimInstance.h"

#include "Pets/BasePet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UPetAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Pet = Cast<ABasePet>(TryGetPawnOwner());
	if (Pet)
	{
		PetMovementComponent = Pet->GetCharacterMovement();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Pet is null"));
	}
}

void UPetAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (PetMovementComponent)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(PetMovementComponent->Velocity);
	}
}
