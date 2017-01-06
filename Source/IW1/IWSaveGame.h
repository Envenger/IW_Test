// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "IWSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class IW1_API UIWSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UIWSaveGame(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, Category = Basic)
	int32 HighestScore;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;
};
