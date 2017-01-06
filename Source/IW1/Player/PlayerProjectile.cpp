// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "Enemy/BaseEnemyActor.h"
#include "PlayerProjectile.h"


APlayerProjectile::APlayerProjectile()
{
	ProjectileDamage = 40;
}

void APlayerProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (OtherActor->IsA(ABaseEnemyActor::StaticClass()))
	{
		ABaseEnemyActor* Enemy = Cast<ABaseEnemyActor>(OtherActor);
		Enemy->EnemyTakeDamage(ProjectileDamage);
		Destroy();
	}
}

