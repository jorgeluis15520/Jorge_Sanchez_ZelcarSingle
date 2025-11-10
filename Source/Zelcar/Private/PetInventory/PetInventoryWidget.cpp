// Fill out your copyright notice in the Description page of Project Settings.


#include "PetInventory/PetInventoryWidget.h"

#include "Components/WrapBox.h"
#include "PetInventory/PetSlotWidget.h"

void UPetInventoryWidget::PopulateInventory(const TArray<FPetInventoryItem>& Pets)
{
	if (!PetsContainer || !PetSlotWidget) return;

	PetsContainer->ClearChildren();
	for (const FPetInventoryItem& PetItem : Pets)
	{
		if (!PetItem.PetData) continue;

		UPetSlotWidget* PetSlot = CreateWidget<UPetSlotWidget>(GetWorld(), PetSlotWidget);
		PetSlot->InitPetSlot(PetItem.PetData);
		PetSlot->OnPetSlotClicked.AddDynamic(this, &UPetInventoryWidget::OnPetSlotSelected);
		PetsContainer->AddChild(PetSlot);
	}
}

void UPetInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPetInventoryWidget::OnPetSlotSelected(UPetDataAsset* PetData)
{
	if (PetData)
	{
		OnPetSelected.Broadcast(PetData);
	}
}
