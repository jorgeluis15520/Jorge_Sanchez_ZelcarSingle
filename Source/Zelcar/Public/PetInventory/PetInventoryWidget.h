// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PetInventory/PetInventoyItem.h"
#include "PetInventoryWidget.generated.h"

class UPetSlotWidget;
class UPetDataAsset;
class UWrapBox;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPetSelected, UPetDataAsset*, SelectedPet);

UCLASS()
class ZELCAR_API UPetInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void OnPetSlotSelected(UPetDataAsset* PetData);
	
public:
	UPROPERTY(meta = (BindWidget))
	UWrapBox* PetsContainer;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPetSlotWidget> PetSlotWidget;

	UPROPERTY(BlueprintAssignable)
	FOnPetSelected OnPetSelected;
	
	void PopulateInventory(const TArray<FPetInventoryItem>& Pets);
};
