// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy/BaseEnemyMovableActor.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class IW1_API ATank : public ABaseEnemyMovableActor
{
	GENERATED_BODY()

public:

	ATank();

	virtual void BeginPlay();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MeshComponents)
	class UStaticMeshComponent* TankNozzel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MeshComponents)
	class UStaticMeshComponent* TankWheels;

	virtual void Tick(float DeltaTime) override;

	const float CalculateProjectileLaunchAngle(float TargetHeight, float TargetDistance, float ProjectileVelocity, float ProjectileGravity) const;

	void FireProjectile() override;

	float ProjectileVelocity;

	float ProjectileGravity;

};
