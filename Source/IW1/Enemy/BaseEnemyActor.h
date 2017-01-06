// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Enemy/EnemyProjectile.h"
#include "Player/PickUps//BasePickUpClass.h"
#include "BaseEnemyActor.generated.h"

class AEnemyUnitsSpawner;
class APlayerPawn;

USTRUCT()
struct FPickUpStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = PickUps)
	TSubclassOf<ABasePickUpClass> PickUpClass;

	UPROPERTY(EditDefaultsOnly, Category = PickUps)
	float DropChancePercentage;

	FPickUpStruct()
	{
		PickUpClass = nullptr;
		DropChancePercentage = 0;
	}
};

UCLASS()
class IW1_API ABaseEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseEnemyActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY()
	AEnemyUnitsSpawner* EnemeySpawner;

	virtual void EnemyTakeDamage(float Damage);

	UPROPERTY(EditDefaultsOnly, Category = Stats)
	float EnemyScorePoints;

	UPROPERTY(EditDefaultsOnly, Category = Stats)
	float Health;

	UPROPERTY(EditDefaultsOnly, Category = Stats)
	bool bIsStompable;

	virtual void DestroyUnit(bool bSpawnDestructable = false);

	UPROPERTY(EditDefaultsOnly, Category = PickUps)
	TArray<FPickUpStruct> PickUpItems;

	void DropItem();


};
