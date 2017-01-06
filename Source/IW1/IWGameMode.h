// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "IWGameMode.generated.h"

/**
 * 
 */
UCLASS()
class IW1_API AIWGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	AIWGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay();

	float ScoreTimeCoeffcient;

	int32 GameScore;

	int32 HighestScore;

	void AddGameScore(float AdditonalScore);
	
	/* Called when game ends */
	void GameWon();

};
