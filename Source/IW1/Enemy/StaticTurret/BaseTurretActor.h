// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy/BaseEnemyFiringActor.h"
#include "Player/PlayerPawn.h"
#include "BaseTurretActor.generated.h"

UCLASS()
class IW1_API ABaseTurretActor : public ABaseEnemyFiringActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTurretActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MeshComponents)
	class UStaticMeshComponent* TurretHead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MeshComponents)
	class UStaticMeshComponent* TurretBase;

	UPROPERTY(EditDefaultsOnly, Category = Destruct)
	TSubclassOf<AActor> TurretHeadDestructable;

	UPROPERTY(EditDefaultsOnly, Category = Destruct)
	TSubclassOf<AActor> TurretBaseDestructable;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	float LastFireTime;

	void FireProjectile() override;

	float ProjectileSpeed;
	
	const FRotator GetTurretHeadDirection(const FVector TurretLocation, const FVector PlayerLocation) const;

	virtual void DestroyUnit(bool bSpawnDestructable = false) override;
};
