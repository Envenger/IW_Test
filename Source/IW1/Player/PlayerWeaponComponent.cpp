// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "Projectile/BaseProjectile.h"
#include "PlayerWeaponComponent.h"


// Sets default values for this component's properties
UPlayerWeaponComponent::UPlayerWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	LastFiredWeapon = 0;
	LastFireTime = 0;

	FiringDelay = 0.3;
}


// Called when the game starts
void UPlayerWeaponComponent::InitializeComponent()
{
	Super::InitializeComponent();

	// ...
	
}


// Called every frame
void UPlayerWeaponComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

bool UPlayerWeaponComponent::ProcessWeaponFire()
{
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	if ((CurrentTime - LastFireTime) >= FiringDelay)
	{
		const uint8 WeaponToFire = GetWeaponToFire();
		FVector FiringLocation;
		FRotator FiringRotation;
		GetFiringLocation(WeaponToFire, FiringLocation, FiringRotation);
		SpawnMuzzleFlash(WeaponToFire);
		FireNormalProjectile(FiringLocation, FiringRotation);
		LastFiredWeapon = WeaponToFire;
		LastFireTime = CurrentTime;
		return true;
	}
	return false;
}

void UPlayerWeaponComponent::SpawnMuzzleFlash(const uint8 WeaponToFire)
{
	RightMuzzlePSC = UGameplayStatics::SpawnEmitterAttached(MuzzleFX, GetWeaponMesh(WeaponToFire), NormalFireSocketName);
	RightMuzzlePSC->SetWorldScale3D(FVector(2.5));
}

const uint8 UPlayerWeaponComponent::GetWeaponToFire() const
{
	if (LastFiredWeapon == 1)
	{
		return 2;
	}
	else if (LastFiredWeapon == 2)
	{
		return 1;
	}
	else
	{
		return FMath::RandRange(1, 2);
	}
}

UStaticMeshComponent* UPlayerWeaponComponent::GetWeaponMesh(const uint8 WeaponIndex) const
{
	if (WeaponIndex == 1)
	{
		return RightHand;
	}
	else if (WeaponIndex == 2)
	{
		return LeftHand;
	}
	else
	{
		return nullptr;
	}
}

void UPlayerWeaponComponent::GetFiringLocation(const uint8 WeaponIndex, FVector &FiringLocation, FRotator &FiringRotation)
{
	UStaticMeshComponent* WeaponMesh = GetWeaponMesh(WeaponIndex);
	FiringLocation = WeaponMesh->GetSocketLocation(NormalFireSocketName);
	FiringRotation = WeaponMesh->GetSocketRotation(NormalFireSocketName);
}


void UPlayerWeaponComponent::FireNormalProjectile(const FVector ProjectileSpawnLocation, const FRotator ProjectileSpawnRotation)
{
	if (FiringSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FiringSound, GetOwner()->GetActorLocation(), 0.4);
	}
	GetWorld()->SpawnActor<ABaseProjectile>(NormalProjectileClass, ProjectileSpawnLocation, ProjectileSpawnRotation);
}

void UPlayerWeaponComponent::DoWeaponRecoil(const uint8 Weapon, float RecoilForce)
{
	
}
