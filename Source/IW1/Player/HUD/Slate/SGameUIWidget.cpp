// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "Player/HUD/IWHUD.h"
#include "SGameUIWidget.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SGameUIWidget::Construct(const FArguments& InArgs)
{
	HUDPtr = InArgs._HUDPtr;
	ChildSlot
	[
		SAssignNew(GameUIOverlay, SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Top)
		.Padding(FMargin(0, 10, 0, 0))
		[
			SNew(SBox)
			[
				SNew(SImage)
				.Image(&HUDPtr->ScoreBorder)
			]
		]
		+ SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Top)
		.Padding(FMargin(0, 10, 0, 0))
		[
			SNew(SBox)
			.Padding(FMargin(10.5, 40.5, 0, 0))
			[
				SNew(STextBlock)
				.Font(HUDPtr->ScoreFont)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor(101, 91, 101))
				.Text(this, &SGameUIWidget::GetScore)
			]
		]
		+ SOverlay::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Bottom)
		[
			SNew(SBox)
			[
				SNew(SImage)
				.Image(&HUDPtr->RoundBorder)
			]
		]
		+ SOverlay::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Bottom)
		[
			SNew(SBox)
			.Padding(FMargin(33, 0, 0, 28))
			[
				SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.Font(HUDPtr->ScoreFont)
				.ColorAndOpacity(FColor(242, 235, 242))
				.Text(this, &SGameUIWidget::GetRound)
			]
		]
		+ SOverlay::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Bottom)
		[
			SNew(SBox)
			[
				SNew(SImage)
				.Image(&HUDPtr->HighestScoreBorder)
			]
		]
		+ SOverlay::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Bottom)
		[
			SNew(SBox)
			.Padding(FMargin(0, 0, 33, 28))
			[
				SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.Font(HUDPtr->ScoreFont)
				.ColorAndOpacity(FColor(242,235,242))
				.Text(this, &SGameUIWidget::GetHighestScore)
			]
		]
		+ SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Bottom)
		[
			SNew(SBox)
			.HeightOverride(290 / 2.2)
			.WidthOverride(1866 / 2.2)
			.Padding(FMargin(0, 0, 0, 10))
			[
				SNew(SImage)
				.Image(&HUDPtr->HealthBarMaterialBrush)
			]
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
/**/
FString SGameUIWidget::GetScore() const
{
	return FString::FromInt(HUDPtr->GameScore);
}

FString SGameUIWidget::GetRound() const
{
	return FString::FromInt(1);
}

FString SGameUIWidget::GetHighestScore() const
{
	return FString::FromInt(HUDPtr->HighestScore);
}
