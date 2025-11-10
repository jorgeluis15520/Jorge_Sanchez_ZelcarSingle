// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PetDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class ZELCAR_API UPetDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pet Data")
	FName PetID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pet Data")
	FText PetName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pet Appearance")
	TObjectPtr<USkeletalMesh> SkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pet Pet Appearance")
	TSubclassOf<UAnimInstance> AnimationBlueprint;
};
