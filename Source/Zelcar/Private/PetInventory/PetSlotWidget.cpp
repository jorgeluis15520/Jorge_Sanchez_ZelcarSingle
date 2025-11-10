// Fill out your copyright notice in the Description page of Project Settings.


#include "PetInventory/PetSlotWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Pets/PetDataAsset.h"

void UPetSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (PetSlotButton)
	{
		PetSlotButton->OnClicked.AddDynamic(this, &UPetSlotWidget::HandleButtonClicked);
	}
}

void UPetSlotWidget::HandleButtonClicked()
{
	OnPetSlotClicked.Broadcast(PetDataAsset);
}

void UPetSlotWidget::InitPetSlot(UPetDataAsset* PetData)
{
	PetDataAsset = PetData;
	if (PetDataAsset)
	{
		PetNameText->SetText(PetDataAsset->PetName);
	}
}
