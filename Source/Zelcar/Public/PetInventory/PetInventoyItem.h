// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pets/PetDataAsset.h"
#include "PetInventoyItem.generated.h"

USTRUCT(BlueprintType)
struct FPetInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPetDataAsset> PetData;

	UPROPERTY(EditAnywhere)
	bool bIsActive = false;

	FPetInventoryItem() : PetData(nullptr), bIsActive(false) {}
};
