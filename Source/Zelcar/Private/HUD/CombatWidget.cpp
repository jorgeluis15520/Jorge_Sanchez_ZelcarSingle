// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/CombatWidget.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"

void UCombatWidget::SetFeedbackText(const FString& NewText)
{
	if (FeedbackText)
	{
		FeedbackText->SetText(FText::FromString(NewText));
	}
}

void UCombatWidget::ShowCombatOverlay()
{
	if (CombatOverlay)
	{
		CombatOverlay->SetVisibility(ESlateVisibility::Visible);
	}
}

void UCombatWidget::HideCombatOverlay()
{
	if (CombatOverlay)
	{
		CombatOverlay->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCombatWidget::ShowFeedbackOverlay()
{
	if (FeedbackOverlay)
	{
		FeedbackOverlay->SetVisibility(ESlateVisibility::Visible);
	}
}

void UCombatWidget::HideFeedBackOverlay()
{
	if (FeedbackOverlay)
	{
		FeedbackOverlay->SetVisibility(ESlateVisibility::Hidden);
	}
}
