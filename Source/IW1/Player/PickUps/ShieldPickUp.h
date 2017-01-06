// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Player/PickUps/BasePickUpClass.h"
#include "ShieldPickUp.generated.h"

/**
 * 
 */
UCLASS()
class IW1_API AShieldPickUp : public ABasePickUpClass
{
	GENERATED_BODY()

	AShieldPickUp();
	
	UPROPERTY(EditDefaultsOnly, Category = PickUp)
	int32 ShieldRestoration;

	virtual void PickUpEffect(APlayerPawn* Player) override;
};
