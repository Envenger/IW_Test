// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "Player/PlayerPawn.h"
#include "IWGameMode.h"
#include "Player/HUD/IWHUD.h"
#include "HealthPickUp.h"

AHealthPickUp::AHealthPickUp()
{
	HealthRestoration = 30;
	Score = 50;
}

void AHealthPickUp::PickUpEffect(APlayerPawn* Player)
{
	AIWGameMode* GameMode = Cast<AIWGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->AddGameScore(Score);

	Player->EventHealth = FMath::Min(Player->MaxPlayerHealth, (Player->EventHealth.GetValue() + HealthRestoration));
}

