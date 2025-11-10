// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PetSlotWidget.generated.h"

class UButton;
class UPetDataAsset;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPetSlotClicked, UPetDataAsset*, PetData);

UCLASS()
class ZELCAR_API UPetSlotWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
public:
	UPROPERTY(meta = (BindWidget))
	UButton* PetSlotButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PetNameText;
	
	UPROPERTY(BlueprintReadOnly)
	UPetDataAsset* PetDataAsset;

	UPROPERTY(BlueprintAssignable)
	FOnPetSlotClicked OnPetSlotClicked;

	void InitPetSlot(UPetDataAsset* PetData);
	
	UFUNCTION()
	void HandleButtonClicked();
};
