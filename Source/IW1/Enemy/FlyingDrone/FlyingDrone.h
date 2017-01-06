// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy/BaseEnemyActor.h"
#include "Enemy/EnemyUnitsSpawner.h"
#include "FlyingDrone.generated.h"

UENUM(BlueprintType)
enum class EFlyingState : uint8
{
	Up UMETA(DisplayName = "Up"),
	Down UMETA(DisplayName = "Down"),
	None UMETA(DisplayName = "None")
};


UCLASS()
class IW1_API AFlyingDrone : public ABaseEnemyActor
{
	GENERATED_BODY()

public:

	AFlyingDrone();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = Flight)
	float StartFlightHeight;

	/** Takes the start height and Ysection Diff into account */
	float VerticalSpeed;

	/** Equal to the one given in the enemy Spawner */
	float ForwardMovementSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Flight)
	int32 YSectionDifference;

	EMovementDirection MovementDirection;

	float PlatformStartYLoc;

	float PlatformEndYLoc;

	float EndFlyingYLoc;
	
	UPROPERTY(EditDefaultsOnly, Category = Flight)
	float SideMovementSpeed;

	const FVector GetNextMoveLocation(const float DeltaTime);

	EFlyingState FlyingState;

};
