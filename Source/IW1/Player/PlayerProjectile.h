// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectile/BaseProjectile.h"
#include "PlayerProjectile.generated.h"

/**
 * 
 */
UCLASS()
class IW1_API APlayerProjectile : public ABaseProjectile
{
	GENERATED_BODY()

public:

	APlayerProjectile();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
};
