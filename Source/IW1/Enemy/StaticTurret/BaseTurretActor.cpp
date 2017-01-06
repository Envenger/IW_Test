// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "Player/PlayerPawn.h"
#include "Enemy/EnemyProjectile.h"
#include "BaseTurretActor.h"


// Sets default values
ABaseTurretActor::ABaseTurretActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretBase"));
	if (TurretBase)
	{
		RootComponent = TurretBase;
	}

	TurretHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretHead"));
	if (TurretHead)
	{
		TurretHead->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}

	MinProjectileFireDelay = 0.7;
	MaxProjectileFireDelay = 0.7;
	ProjectileSpeed = 0;
}

// Called when the game starts or when spawned
void ABaseTurretActor::BeginPlay()
{
	ABaseEnemyActor::BeginPlay();

	for (TActorIterator<APlayerPawn> PlayerSpawnItr(GetWorld()); PlayerSpawnItr; ++PlayerSpawnItr)
	{
		PlayerActor = *PlayerSpawnItr;
	}
	LastFireTime = 0;

	ProjectileSpeed = Cast<AEnemyProjectile>(NormalProjectileClass->GetDefaultObject())->ProjectileComponent->InitialSpeed;
}

// Called every frame
void ABaseTurretActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (PlayerActor)
	{
		FVector TurretLocation = TurretHead->RelativeLocation + GetActorLocation();
		FVector PlayerLocation = PlayerActor->GetActorLocation();
		if ((TurretLocation.X - PlayerLocation.X) < 8000 && (TurretLocation.X - PlayerLocation.X) > 200)
		{
			FRotator Direction = GetTurretHeadDirection(TurretLocation, PlayerLocation);
			TurretHead->SetRelativeRotation(Direction);
			float CurrentTime = GetWorld()->GetTimeSeconds();
			if ((CurrentTime - LastFireTime) > MinProjectileFireDelay)
			{
				FireProjectile();
				LastFireTime = CurrentTime;
			}
		}
	}
}

const FRotator ABaseTurretActor::GetTurretHeadDirection(const FVector TurretLocation, const FVector PlayerLocation) const
{
	//return (PlayerLocation - TurretLocation).Rotation();
	FVector PlayerVelocity = PlayerActor->CurrentVelocity;
	PlayerVelocity.X /= FMath::FRandRange(1.22, 1.32);
	float Time = (PlayerLocation - TurretLocation).Size() / (ProjectileSpeed - PlayerVelocity.Size());

	FVector PlayerDisplacement = (Time*PlayerVelocity);
	PlayerDisplacement.Y = FMath::Sign(PlayerDisplacement.Y)*(FMath::Min(FMath::Abs(PlayerDisplacement.Y), 275.f));
	FVector MovedTarget = PlayerLocation + PlayerDisplacement;

	return (MovedTarget - TurretLocation).Rotation();
}

void ABaseTurretActor::FireProjectile()
{
	FRotator SpawnRotation = TurretHead->GetSocketRotation("FiringSocket");
	SpawnRotation.Pitch += FMath::FRandRange(-0.5, 0.5);
	SpawnRotation.Yaw += FMath::FRandRange(-0.5, 0.5);
	FVector SpawnLocation = TurretHead->GetSocketLocation("FiringSocket");
	GetWorld()->SpawnActor<ABaseProjectile>(NormalProjectileClass, SpawnLocation, SpawnRotation);
	PlayMuzzleEffects(TurretHead, "FiringSocket", FVector(3.2), 0.2);
}

void ABaseTurretActor::DestroyUnit(bool bSpawnDestructable)
{
	if (bSpawnDestructable == true)
	{
		GetWorld()->SpawnActor<AActor>(TurretBaseDestructable, TurretBase->GetComponentLocation(), TurretBase->GetComponentRotation());
		GetWorld()->SpawnActor<AActor>(TurretHeadDestructable, TurretHead->GetComponentLocation(), TurretHead->GetComponentRotation());
	}
	Super::DestroyUnit();
}