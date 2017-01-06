// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "HoverCraft.h"

AHoverCraft::AHoverCraft()
{
	HoverBase = CreateDefaultSubobject<USceneComponent>(TEXT("HoverBase"));
	if (HoverBase)
	{
		RootComponent = HoverBase;
	}
	if (EnemyMesh)
	{
		EnemyMesh->AttachTo(HoverBase);
	}
	bHoveringUp = true;
	MinHoverHeight = 35;
	MaxHoverHeight = 55;
	MinHoverVerticalSpeed = 5;
	MaxHoverVerticalSpeed = 15;

	MinProjectileFireDelay = 5;
	MaxProjectileFireDelay = 10;


}

void AHoverCraft::BeginPlay()
{
	Super::BeginPlay();

	CurrentHoverSpeed = FMath::RandRange(MinHoverVerticalSpeed, MaxHoverVerticalSpeed);
}

void AHoverCraft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float HoverHeight = EnemyMesh->RelativeLocation.Z;
	if (bHoveringUp)
	{
		HoverHeight += CurrentHoverSpeed*DeltaTime;
		if (HoverHeight > MaxHoverHeight)
		{
			HoverHeight = MaxHoverHeight;
			CurrentHoverSpeed = FMath::RandRange(MinHoverVerticalSpeed, MaxHoverVerticalSpeed);
			bHoveringUp = false;
		}
	}
	else
	{
		HoverHeight -= CurrentHoverSpeed*DeltaTime;
		if (HoverHeight < MinHoverHeight)
		{
			HoverHeight = MinHoverHeight;
			CurrentHoverSpeed = FMath::RandRange(MinHoverVerticalSpeed, MaxHoverVerticalSpeed);
			bHoveringUp = true;
		}
	}
	EnemyMesh->RelativeLocation.Z = HoverHeight;
	

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

void AHoverCraft::FireProjectile()
{
	if (CanFireProjectile())
	{
		//if (FMath::RandRange(1, 15) == 15)
		//{
			//Powershot
		//}
		FRotator SpawnRotation = EnemyMesh->GetSocketRotation("NormalFiringSocket");
		FVector SpawnLocation = EnemyMesh->GetSocketLocation("NormalFiringSocket");
		GetWorld()->SpawnActor<ABaseProjectile>(NormalProjectileClass, SpawnLocation, SpawnRotation);
		PlayMuzzleEffects(EnemyMesh, "NormalFiringSocket", FVector(2.1), 0.2);
	}
	Super::FireProjectile();
}
