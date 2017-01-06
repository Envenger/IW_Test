// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy/BaseEnemyFiringActor.h"
#include "Enemy/EnemyUnitsSpawner.h"
#include "BaseEnemyMovableActor.generated.h"

/**
 * 
 */
UCLASS()
class IW1_API ABaseEnemyMovableActor : public ABaseEnemyFiringActor
{
	GENERATED_BODY()

public:
	ABaseEnemyMovableActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MeshComponents)
	class UStaticMeshComponent* EnemyMesh;

	virtual void Tick(float DeltaTime) override;

	const bool CanFireProjectile() const;

	FMovementSection CurrentSectionLocation;

	FMovementSection NextMovementSection;
	
	virtual void DestroyUnit(bool bSpawnDestructable = false) override;

///////////////////////////////////////////////////////
// Player Fire detection

	UPROPERTY(EditdefaultsOnly, Category = Projectile)
		float DetectionFireDelay;

	UPROPERTY(EditdefaultsOnly, Category = Projectile)
		float FiringDetectionWidth;

	/** CHance the enemy will fire once per second(Complicated adjust to value to see how it works)*/
	UPROPERTY(EditdefaultsOnly, Category = Projectile)
		float DetectionFireChancePerSecond;
};
