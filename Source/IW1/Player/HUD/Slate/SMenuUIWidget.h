// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Player/HUD/IWHUD.h"
/**
 * 
 */
class IW1_API SMenuUIWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMenuUIWidget)
		: _HUDPtr()
		, _MenuType(EMenuOpenType::None)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AIWHUD>, HUDPtr)
	SLATE_ATTRIBUTE(EMenuOpenType, MenuType)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FReply ExitButtonClicked();

	FReply RestartButtonClicked();

	const FSlateBrush* GetMenuIcon() const; 

protected:
	TWeakObjectPtr<class AIWHUD> HUDPtr;

	EMenuOpenType MenuType;


};
