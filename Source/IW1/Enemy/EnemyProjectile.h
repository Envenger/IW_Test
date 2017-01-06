// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectile/BaseProjectile.h"
#include "EnemyProjectile.generated.h"

/**
 * 
 */
UCLASS()
class IW1_API AEnemyProjectile : public ABaseProjectile
{
	GENERATED_BODY()
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	
};
