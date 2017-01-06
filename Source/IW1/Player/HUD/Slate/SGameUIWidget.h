// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/SCompoundWidget.h"
#include "Player/HUD/IWHUD.h"

class IW1_API SGameUIWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGameUIWidget)
		: _HUDPtr()
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AIWHUD>, HUDPtr)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	/** The box containing the inventory */
	TSharedPtr<SOverlay> GameUIOverlay;

	FText GetScore() const;

	FText GetRound() const;

	FText GetHighestScore() const;

protected:
	TWeakObjectPtr<class AIWHUD> HUDPtr;

};
