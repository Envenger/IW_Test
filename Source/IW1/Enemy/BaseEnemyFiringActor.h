// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy/BaseEnemyActor.h"
#include "BaseEnemyFiringActor.generated.h"

/**
 * 
 */
UCLASS()
class IW1_API ABaseEnemyFiringActor : public ABaseEnemyActor
{
	GENERATED_BODY()

public:

	ABaseEnemyFiringActor();

	virtual void BeginPlay() override;

	UPROPERTY()
	APlayerPawn* PlayerActor;

	UPROPERTY(EditDefaultsOnly, Category = Projectie)
	TSubclassOf<ABaseProjectile> NormalProjectileClass;

	virtual void FireProjectile();

	/** execute fire irrespective of firing delay and resets the delay */
	void ExecuteFire();

	FTimerHandle ProjectileDelayHandle;

	const bool CanFireProjectile() const;

	UPROPERTY(EditdefaultsOnly, Category = Projectile)
	float MinProjectileFireDelay;

	UPROPERTY(EditdefaultsOnly, Category = Projectile)
	float MaxProjectileFireDelay;

	/** FX for muzzle flash */
	UPROPERTY(EditDefaultsOnly, Category = Effects)
	UParticleSystem* MuzzleFX;

	/** spawned component for muzzle FX */
	UPROPERTY()
	UParticleSystemComponent* MuzzlePSC;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* FiringSound;

	virtual void PlayMuzzleEffects(USceneComponent* Scene, const FName SocketName, const FVector FXScale, const float VolumeMultiplier = 0.2);

	/** Min is repeated so that higher numbers are rarer */
	const float CalculateFireDelay() const;
	
	
};
