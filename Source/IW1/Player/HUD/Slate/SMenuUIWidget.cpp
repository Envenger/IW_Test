// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "Player/HUD/IWHUD.h"
#include "SMenuUIWidget.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMenuUIWidget::Construct(const FArguments& InArgs)
{
	HUDPtr = InArgs._HUDPtr;
	
	MenuType = InArgs._MenuType.Get();

	ChildSlot
	[
		SNew(SBox)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SImage)
				.Image(this, &SMenuUIWidget::GetMenuIcon)
			]
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.Padding(FMargin(0,60,0,0))
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.FillWidth(50)
				[
					SNew(SButton)
					.ButtonStyle(&HUDPtr->RestartButtonStyle)
					.OnClicked(this, &SMenuUIWidget::RestartButtonClicked)
				]
				+ SHorizontalBox::Slot()
				.Padding(FMargin(20,0,0,0))
				.FillWidth(50)
				[
					SNew(SButton)
					.ButtonStyle(&HUDPtr->ExitButtonStyle)
					.OnClicked(this, &SMenuUIWidget::ExitButtonClicked)
				]
			]
		]
	];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION


FReply SMenuUIWidget::ExitButtonClicked()
{
	HUDPtr->ExitGameClicked();
	return FReply::Handled();
}

FReply SMenuUIWidget::RestartButtonClicked()
{
	HUDPtr->RestartGameClicked();
	return FReply::Handled();
}

const FSlateBrush* SMenuUIWidget::GetMenuIcon() const
{
	if (MenuType == EMenuOpenType::Won)
	{
		return &HUDPtr->WinningMenuFrame;
	}
	else if (MenuType == EMenuOpenType::Lost)
	{
		return &HUDPtr->LosingMenuFrame;
	}
	else
	{
		return &HUDPtr->NoneMenuFrame;
	}
}