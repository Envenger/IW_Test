// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "Player/PlayerPawn.h"
#include "EnemyProjectile.h"



void AEnemyProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (OtherActor->IsA(APlayerPawn::StaticClass()))
	{
		APlayerPawn* PlayerPawn = Cast<APlayerPawn>(OtherActor);
		PlayerPawn->EventHealth -= ProjectileDamage;
		Destroy();
	}
}



