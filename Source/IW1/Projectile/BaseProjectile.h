// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

UCLASS()
class IW1_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

	/** Dummy root to attach the capsule */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ProjectileComponents)
	class USceneComponent* DummyRoot;

	/** Collision capsule for the projectile */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ProjectileComponents)
	class UCapsuleComponent* ProjectileCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ProjectileComponents)
	class UProjectileMovementComponent* ProjectileComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	float LifeTime;

	UPROPERTY(EditDefaultsOnly, Category = ProjectileComponents)
	float ProjectileDamage;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
