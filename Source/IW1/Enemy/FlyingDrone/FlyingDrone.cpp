// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "FlyingDrone.h"

AFlyingDrone::AFlyingDrone()
{
	StartFlightHeight = 2100;
	YSectionDifference = 14;
	MovementDirection = EMovementDirection::None;
	FlyingState = EFlyingState::Down;

	ForwardMovementSpeed = 0;
	SideMovementSpeed = 0;
}


void AFlyingDrone::BeginPlay()
{
	Super::BeginPlay();
}

void AFlyingDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NextMovementLocation = GetNextMoveLocation(DeltaTime);
	SetActorLocation(NextMovementLocation);
}

const FVector AFlyingDrone::GetNextMoveLocation(const float DeltaTime)
{
	FVector NextMovementLocation = GetActorLocation();
	NextMovementLocation.X += ForwardMovementSpeed*DeltaTime;



	if (MovementDirection == EMovementDirection::Right)
	{
		NextMovementLocation.Y += SideMovementSpeed*DeltaTime;
		if (FlyingState == EFlyingState::Down && NextMovementLocation.Y >= PlatformStartYLoc)
		{
			FlyingState = EFlyingState::None;
		}
		else if (FlyingState == EFlyingState::None && NextMovementLocation.Y >= PlatformEndYLoc)
		{
			FlyingState = EFlyingState::Up;
		}
		else if (FlyingState == EFlyingState::Up && NextMovementLocation.Y >= EndFlyingYLoc)
		{
			Destroy();
		}
	}
	else if (MovementDirection == EMovementDirection::Left)
	{
		NextMovementLocation.Y -= SideMovementSpeed*DeltaTime;
		if (FlyingState == EFlyingState::Down && NextMovementLocation.Y <= PlatformEndYLoc)
		{
			FlyingState = EFlyingState::None;
		}
		else if (FlyingState == EFlyingState::None && NextMovementLocation.Y <= PlatformStartYLoc)
		{
			FlyingState = EFlyingState::Up;
		}
		else if (FlyingState == EFlyingState::Up && NextMovementLocation.Y <= EndFlyingYLoc)
		{
			Destroy();
		}
	}

	if (FlyingState == EFlyingState::Up)
	{
		NextMovementLocation.Z += VerticalSpeed*DeltaTime;
	}
	else if (FlyingState == EFlyingState::Down)
	{
		NextMovementLocation.Z -= VerticalSpeed*DeltaTime;
	}
	return NextMovementLocation;
}