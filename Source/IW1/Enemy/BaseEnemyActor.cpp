// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "IWGameMode.h"
#include "EnemyUnitsSpawner.h"
#include "Player/PlayerPawn.h"
#include "BaseEnemyActor.h"


// Sets default values
ABaseEnemyActor::ABaseEnemyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsStompable = true;

	EnemyScorePoints = 50;

	Health = 100;
}

// Called when the game starts or when spawned
void ABaseEnemyActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseEnemyActor::EnemyTakeDamage(float Damage)
{
	Health = FMath::Max(0.f, Health - Damage);
	if (Health == 0)
	{
		AIWGameMode* GameMode = Cast<AIWGameMode>(GetWorld()->GetAuthGameMode());
		GameMode->AddGameScore(EnemyScorePoints);

		DestroyUnit();
	}
}

void ABaseEnemyActor::DestroyUnit(bool bSpawnDestructable)
{
	DropItem();
	Destroy();
}

void ABaseEnemyActor::DropItem()
{
	for (FPickUpStruct PickUpStruct : PickUpItems)
	{
		if (PickUpStruct.PickUpClass)
		{
			int32 RandChance = FMath::RandRange(1, 100);
			if (RandChance < PickUpStruct.DropChancePercentage)
			{
				const FVector SpawnLocation = GetActorLocation();
				const FRotator SpawnRotation = GetActorRotation();
				GetWorld()->SpawnActor<ABasePickUpClass>(PickUpStruct.PickUpClass, SpawnLocation, SpawnRotation);
			}
		}
	}
}