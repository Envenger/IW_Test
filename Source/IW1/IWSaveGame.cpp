// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "IWSaveGame.h"

UIWSaveGame::UIWSaveGame(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SaveSlotName = TEXT("ScoreSaveSlot");
	UserIndex = 0;
	HighestScore = 0;
}

