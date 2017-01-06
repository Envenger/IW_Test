// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy/BaseEnemyMovableActor.h"
#include "HoverCraft.generated.h"

/**
 * 
 */
UCLASS()
class IW1_API AHoverCraft : public ABaseEnemyMovableActor
{
	GENERATED_BODY()
	
public:

	AHoverCraft();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MeshComponents)
	class USceneComponent* HoverBase;

	virtual void Tick(float DeltaTime) override;
	
	bool bHoveringUp;

	float CurrentHoverSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Hover)
	float MaxHoverHeight;

	UPROPERTY(EditDefaultsOnly, Category = Hover)
	float MinHoverHeight;

	UPROPERTY(EditDefaultsOnly, Category = Hover)
	float MaxHoverVerticalSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Hover)
	float MinHoverVerticalSpeed;

	void FireProjectile() override;


};
