// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "Enemy/EnemyUnitsSpawner.h"
#include "BaseEnemyMovableActor.h"

ABaseEnemyMovableActor::ABaseEnemyMovableActor()
{
	
	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	if (EnemyMesh)
	{
		RootComponent = EnemyMesh;
	}

	MinProjectileFireDelay = 0.6;
	MaxProjectileFireDelay = 4;

	FiringDetectionWidth = 30;
	DetectionFireDelay = 2.5;
	DetectionFireChancePerSecond = 20;
}

void ABaseEnemyMovableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const bool ABaseEnemyMovableActor::CanFireProjectile() const
{
	for (int32 i = 0; i < EnemeySpawner->MovingEnemies.Num(); i++)
	{
		if (EnemeySpawner->MovingEnemies[i])
		{
			if (EnemeySpawner->MovingEnemies[i]->CurrentSectionLocation.YSection == CurrentSectionLocation.YSection)
			{
				if (EnemeySpawner->MovingEnemies[i]->CurrentSectionLocation.XSection < CurrentSectionLocation.XSection)
				{
					return false;
				}
			}
		}
	}
	return true;
}

void ABaseEnemyMovableActor::DestroyUnit(bool bSpawnDestructable)
{
	const int32 Index = EnemeySpawner->MovingEnemies.Find(this);
	EnemeySpawner->MovingEnemies[Index] = nullptr;
	Super::DestroyUnit();
}
