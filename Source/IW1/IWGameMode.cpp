// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "IWSaveGame.h"
#include "IWGameMode.h"

AIWGameMode::AIWGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameScore = 0;
	ScoreTimeCoeffcient = 1400 / 180;
}

void AIWGameMode::BeginPlay()
{
	UIWSaveGame* ScoreSave = Cast<UIWSaveGame>(UGameplayStatics::CreateSaveGameObject(UIWSaveGame::StaticClass()));
	if (UGameplayStatics::DoesSaveGameExist(TEXT("ScoreSaveSlot"), 0))
	{
		ScoreSave = Cast<UIWSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("ScoreSaveSlot"), 0));
		HighestScore = ScoreSave->HighestScore;
	}
}

void AIWGameMode::AddGameScore(float AdditonalScore)
{
	GameScore += AdditonalScore;
}

void AIWGameMode::GameWon()
{
	UIWSaveGame* ScoreSave = Cast<UIWSaveGame>(UGameplayStatics::CreateSaveGameObject(UIWSaveGame::StaticClass()));
	if (GameScore > HighestScore)
	{
		ScoreSave->HighestScore = GameScore; 
		UGameplayStatics::SaveGameToSlot(ScoreSave, ScoreSave->SaveSlotName, ScoreSave->UserIndex);
	}
}