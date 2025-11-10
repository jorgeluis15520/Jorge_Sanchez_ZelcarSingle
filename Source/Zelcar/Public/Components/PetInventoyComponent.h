// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PetInventory/PetInventoyItem.h"
#include "PetInventoyComponent.generated.h"

class UPetDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZELCAR_API UPetInventoyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPetInventoyComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, Category = "Pet Inventory")
	TArray<FPetInventoryItem> OwnedPets;

	void AddPet(UPetDataAsset* PetData);
};
