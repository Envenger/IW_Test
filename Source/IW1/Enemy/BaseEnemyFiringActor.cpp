// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "EnemyUnitsSpawner.h"
#include "BaseEnemyFiringActor.h"

ABaseEnemyFiringActor::ABaseEnemyFiringActor()
{
	MinProjectileFireDelay = 5;
	MaxProjectileFireDelay = 10;
}

void ABaseEnemyFiringActor::BeginPlay()
{
	Super::BeginPlay();

	float FiringDelay = CalculateFireDelay();
	GetWorld()->GetTimerManager().SetTimer(ProjectileDelayHandle, this, &ABaseEnemyFiringActor::FireProjectile, FiringDelay, false);
}

const float ABaseEnemyFiringActor::CalculateFireDelay() const
{
	float Rand1 = FMath::FRandRange(MinProjectileFireDelay, MaxProjectileFireDelay);
	float Rand2 = FMath::FRandRange(MinProjectileFireDelay, MaxProjectileFireDelay);
	return FMath::Min(Rand1, Rand2);
}

const bool ABaseEnemyFiringActor::CanFireProjectile() const
{
	return true;
}

void ABaseEnemyFiringActor::FireProjectile()
{
	float FiringDelay = CalculateFireDelay();
	GetWorld()->GetTimerManager().SetTimer(ProjectileDelayHandle, this, &ABaseEnemyFiringActor::FireProjectile, FiringDelay, false);
}

void ABaseEnemyFiringActor::PlayMuzzleEffects(USceneComponent* Scene, const FName SocketName, const FVector FXScale, const float VolumeMultiplier)
{
	MuzzlePSC = UGameplayStatics::SpawnEmitterAttached(MuzzleFX, Scene, SocketName);
	MuzzlePSC->SetWorldScale3D(FXScale);
	if (FiringSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FiringSound, GetActorLocation(), VolumeMultiplier);
	}
}

void ABaseEnemyFiringActor::ExecuteFire()
{
	GetWorld()->GetTimerManager().ClearTimer(ProjectileDelayHandle);
	FireProjectile();
}