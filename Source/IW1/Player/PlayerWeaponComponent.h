// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Projectile/BaseProjectile.h"
#include "PlayerWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IW1_API UPlayerWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerWeaponComponent();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	bool ProcessWeaponFire();

	const uint8 GetWeaponToFire() const;

	/** 1 for right weapon 2 for left weapon */
	uint8 LastFiredWeapon;

	/** Takes a weapon and gets the weapon firing location */
	void GetFiringLocation(const uint8 WeaponIndex, FVector &FiringLocation, FRotator &FiringRotation);

	float LastFireTime;

	/** Delay in firing weapon */
	UPROPERTY(EditDefaultsOnly, Category = WeaponFire)
	float FiringDelay;

	UStaticMeshComponent* GetWeaponMesh(const uint8 WeaponIndex) const;

	UPROPERTY()
	UStaticMeshComponent* LeftHand;

	UPROPERTY()
	UStaticMeshComponent* RightHand;

	FName NormalFireSocketName = "NormalFiringPoint";
	
	UPROPERTY(EditDefaultsOnly, Category = ProjectieClass)
	TSubclassOf<ABaseProjectile> NormalProjectileClass;

	void FireNormalProjectile(const FVector ProjectileSpawnLocation, const FRotator ProjectileSpawnRotation);

	void DoWeaponRecoil(const uint8 Weapon, float RecoilForce);

//////////////////////////////////////////////////
// Effects

	/** FX for muzzle flash */
	UPROPERTY(EditDefaultsOnly, Category = Effects)
	UParticleSystem* MuzzleFX;

	/** spawned component for muzzle FX */
	UPROPERTY()
	UParticleSystemComponent* RightMuzzlePSC;

	/** spawned component for muzzle FX */
	UPROPERTY()
	UParticleSystemComponent* LeftMuzzlePSC;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* FiringSound;

	void SpawnMuzzleFlash(const uint8 Weapon);
};
