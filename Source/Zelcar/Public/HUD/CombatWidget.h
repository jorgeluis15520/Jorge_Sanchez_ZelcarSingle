// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatWidget.generated.h"

class UTextBlock;
class UOverlay;
/**
 * 
 */
UCLASS()
class ZELCAR_API UCombatWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> CombatOverlay;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> FeedbackOverlay;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> FeedbackText;

public:
	UFUNCTION(BlueprintCallable)
	void SetFeedbackText(const FString& NewText);
	UFUNCTION(BlueprintCallable)
	void ShowCombatOverlay();
	UFUNCTION(BlueprintCallable)
	void HideCombatOverlay();
	UFUNCTION(BlueprintCallable)
	void ShowFeedbackOverlay();
	UFUNCTION(BlueprintCallable)
	void HideFeedBackOverlay();
};
