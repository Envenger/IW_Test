// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Player/PickUps/BasePickUpClass.h"
#include "HealthPickUp.generated.h"

/**
 * 
 */
UCLASS()
class IW1_API AHealthPickUp : public ABasePickUpClass
{
	GENERATED_BODY()

	AHealthPickUp();

	UPROPERTY(EditDefaultsOnly, Category = PickUp)
	int32 HealthRestoration;
	
	virtual void PickUpEffect(APlayerPawn* Player) override;
};
