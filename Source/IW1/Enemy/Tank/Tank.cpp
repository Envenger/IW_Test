// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "Tank.h"

ATank::ATank()
{
	TankNozzel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HoverBase"));
	if (TankNozzel)
	{
		TankNozzel->AttachTo(RootComponent);
	}

	TankWheels = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HoverWheels"));
	if (TankWheels)
	{
		TankWheels->AttachTo(RootComponent);
	}

	ProjectileVelocity = 7000;
	ProjectileGravity = 9.8;

	MinProjectileFireDelay = 1.5;
	MaxProjectileFireDelay = 7;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector HoverCraftLoc = GetActorLocation();
	const FVector PlayerLoc = PlayerActor->GetActorLocation();
	const float LocationYDifference = FMath::Abs(HoverCraftLoc.Y - PlayerLoc.Y);
	if (LocationYDifference < FiringDetectionWidth && CanFireProjectile())
	{
		const float FireTimerRunTime = GetWorld()->GetTimerManager().GetTimerElapsed(ProjectileDelayHandle);
		if (FireTimerRunTime >= DetectionFireDelay)
		{
			const float FiringChance = FMath::FRandRange(0, 100);
			if (FiringChance <= DetectionFireChancePerSecond*DeltaTime)
			{
				ExecuteFire();
			}
		}
	}
}

void ATank::FireProjectile()
{
	if (CanFireProjectile())
	{
		FRotator SpawnRotation = TankNozzel->GetSocketRotation("NormalFiringSocket");
		FVector SpawnLocation = TankNozzel->GetSocketLocation("NormalFiringSocket");
		GetWorld()->SpawnActor<ABaseProjectile>(NormalProjectileClass, SpawnLocation, SpawnRotation);
		PlayMuzzleEffects(TankNozzel, "NormalFiringSocket", FVector(3.1), 0.2);
	}

	//else
	//{
	//	FiringDelay = CalculateFireDelay()*4;// Should be higher delay
	//}
	Super::FireProjectile();
}

const float ATank::CalculateProjectileLaunchAngle(float TargetHeight, float TargetDistance, float ProjectileVelocity, float ProjectileGravity) const
{
	float TX = TargetDistance;
	float TY = TargetHeight;
	float G = ProjectileGravity;
	float V = ProjectileVelocity;
	float R1 = FMath::Sqrt(FMath::Pow(V, 4) - G*(G*(FMath::Pow(TX, 2)) + ((2 * TY)*(FMath::Pow(V, 2)))));
	float A1 = FMath::Atan(FMath::Pow(V, 2) + R1) / (G / TY);
	float A2 = FMath::Atan(FMath::Pow(V, 2) - R1) / (G / TY);
	return A1;
}

