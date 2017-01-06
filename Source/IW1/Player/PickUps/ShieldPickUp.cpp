// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "Player/PlayerPawn.h"
#include "IWGameMode.h"
#include "Player/PlayerShieldActor.h"
#include "ShieldPickUp.h"

AShieldPickUp::AShieldPickUp()
{
	Score = 10;
	ShieldRestoration = 100;
}

void AShieldPickUp::PickUpEffect(APlayerPawn* Player)
{
	AIWGameMode* GameMode = Cast<AIWGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->AddGameScore(Score);

	Player->ShieldActor->ShieldTakeDamage(0, -ShieldRestoration);
	Player->ShieldActor->ShieldTakeDamage(1, -ShieldRestoration);
	Player->ShieldActor->ShieldTakeDamage(2, -ShieldRestoration);
}
