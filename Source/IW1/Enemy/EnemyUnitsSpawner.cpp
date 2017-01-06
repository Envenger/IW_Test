// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "BaseEnemyMovableActor.h"
#include "Enemy/StaticTurret/BaseTurretActor.h"
#include "Enemy/FlyingDrone/FlyingDrone.h"
#include "IWGameMode.h"
#include "Player/HUD/IWHUD.h"
#include "EnemyUnitsSpawner.h"

// Sets default values
AEnemyUnitsSpawner::AEnemyUnitsSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LengthOfXSection = 350;
	LengthOfYSection = 250;

	ForwardMovementSpeed = 450;
	SideMovementSpeed = 750;

	MovementDirection = EMovementDirection::None;

	NoOfYSections = 15;

	MinTurrentSpawnDistance = 8;
	MaxTurrentSpawnDistance = 60;
	StaticTurretNextSpawnSection = 10;
	StaticTurretSpawnGap = 30;

	MinFlyingDroneSpawnDistance = 60;
	MaxFlyingDroneSpawnDistance = 120;
	FlyingDroneNextSpawnSection = 0;
	FlyingDroneSpawnGap = 10;
}

void AEnemyUnitsSpawner::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FlyingDroneNextSpawnSection = FMath::RandRange(MinFlyingDroneSpawnDistance, MaxFlyingDroneSpawnDistance);
	if (FMath::RandBool())
	{
		MovementDirection = EMovementDirection::Right;
	}
	else
	{
		MovementDirection = EMovementDirection::Left;
	}
}

// Called when the game starts or when spawned
void AEnemyUnitsSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyUnitsSpawner::SpawnInitalEnemies()
{
	for (int32 i = 5; i <= 11; i++)
	{
		ABaseEnemyMovableActor* Enemy1;
		if ( i == 9 || i == 7)
		{
			Enemy1 = GetWorld()->SpawnActor<ABaseEnemyMovableActor>(TankClass, GetLocationFromSection(FMovementSection(0, i)), FRotator(0, 180, 0));
		}
		else
		{
			Enemy1 = GetWorld()->SpawnActor<ABaseEnemyMovableActor>(HoverCraftClass, GetLocationFromSection(FMovementSection(0, i)), FRotator(0, 180, 0));
		}
		Enemy1->CurrentSectionLocation = FMovementSection(0, i);
		Enemy1->NextMovementSection = Enemy1->CurrentSectionLocation;
		if (MovementDirection == EMovementDirection::Right)
		{
			Enemy1->NextMovementSection.YSection += 1;
		}
		else if (MovementDirection == EMovementDirection::Left)
		{
			Enemy1->NextMovementSection.YSection -= 1;
		}
		Enemy1->EnemeySpawner = this;
		Enemy1->PlayerActor = PlayerPawn;
		MovingEnemies.Add(Enemy1);
	}

	for (int32 i = 7; i <= 9; i++)
	{
		ABaseEnemyMovableActor* Enemy1;
		if (i == 8)
		{
			Enemy1 = GetWorld()->SpawnActor<ABaseEnemyMovableActor>(TankClass, GetLocationFromSection(FMovementSection(1, i)), FRotator(0, 180, 0));
		}
		else
		{
			Enemy1 = GetWorld()->SpawnActor<ABaseEnemyMovableActor>(HoverCraftClass, GetLocationFromSection(FMovementSection(1, i)), FRotator(0, 180, 0));
		}		
		Enemy1->CurrentSectionLocation = FMovementSection(1, i);
		Enemy1->NextMovementSection = Enemy1->CurrentSectionLocation;
		if (MovementDirection == EMovementDirection::Right)
		{
			Enemy1->NextMovementSection.YSection += 1;
		}
		else if (MovementDirection == EMovementDirection::Left)
		{
			Enemy1->NextMovementSection.YSection -= 1;
		}
		Enemy1->EnemeySpawner = this;
		Enemy1->PlayerActor = PlayerPawn;
		MovingEnemies.Add(Enemy1);
	}
	for (int32 i = 6; i <= 10; i++)
	{
		ABaseEnemyMovableActor* Enemy1;
		if (i == 6 || i == 10)
		{
			Enemy1 = GetWorld()->SpawnActor<ABaseEnemyMovableActor>(TankClass, GetLocationFromSection(FMovementSection(2, i)), FRotator(0, 180, 0));
		}
		else
		{
			Enemy1 = GetWorld()->SpawnActor<ABaseEnemyMovableActor>(HoverCraftClass, GetLocationFromSection(FMovementSection(2, i)), FRotator(0, 180, 0));
		}	
		Enemy1->CurrentSectionLocation = FMovementSection(2, i);
		Enemy1->NextMovementSection = Enemy1->CurrentSectionLocation;
		if (MovementDirection == EMovementDirection::Right)
		{
			Enemy1->NextMovementSection.YSection += 1;
		}
		else if (MovementDirection == EMovementDirection::Left)
		{
			Enemy1->NextMovementSection.YSection -= 1;
		}
		Enemy1->EnemeySpawner = this;
		Enemy1->PlayerActor = PlayerPawn;
		MovingEnemies.Add(Enemy1);
	}
	for (int32 i = 5; i <= 11; i++)
	{
		ABaseEnemyMovableActor* Enemy1;
		if (i == 6 || i == 7 || i == 9 || i == 10)
		{
			Enemy1 = GetWorld()->SpawnActor<ABaseEnemyMovableActor>(TankClass, GetLocationFromSection(FMovementSection(3, i)), FRotator(0, 180, 0));
		}
		else
		{
			Enemy1 = GetWorld()->SpawnActor<ABaseEnemyMovableActor>(HoverCraftClass, GetLocationFromSection(FMovementSection(3, i)), FRotator(0, 180, 0));
		}
		Enemy1->CurrentSectionLocation = FMovementSection(2, i);
		Enemy1->NextMovementSection = Enemy1->CurrentSectionLocation;
		if (MovementDirection == EMovementDirection::Right)
		{
			Enemy1->NextMovementSection.YSection += 1;
		}
		else if (MovementDirection == EMovementDirection::Left)
		{
			Enemy1->NextMovementSection.YSection -= 1;
		}
		Enemy1->EnemeySpawner = this;
		Enemy1->PlayerActor = PlayerPawn;
		MovingEnemies.Add(Enemy1);
	}
}

void AEnemyUnitsSpawner::CalculateNextEnemySections()
{
	TArray<FMovementSection> NewMovementSections;
	for (int32 i = 0; i < MovingEnemies.Num(); i++)
	{
		if (MovingEnemies[i])
		{
			FMovementSection NewSection = MovingEnemies[i]->CurrentSectionLocation;
			NewSection.XSection += 1;
			if (MovementDirection == EMovementDirection::Right)
			{
				NewSection.YSection += 1;
				if (NewSection.YSection >(NoOfYSections - 1))
				{
					MovementDirection = EMovementDirection::Left;
					return;
				}
			}
			else if (MovementDirection == EMovementDirection::Left)
			{
				NewSection.YSection -= 1;
				if (NewSection.YSection < 0)
				{
					MovementDirection = EMovementDirection::Right;
					return;
				}
			}
			NewMovementSections.Add(NewSection);
		}
		else
		{
			NewMovementSections.Add(FMovementSection());
		}
	}
	for (int32 i = 0; i < MovingEnemies.Num(); i++)
	{
		if (MovingEnemies[i])
		{
			MovingEnemies[i]->CurrentSectionLocation = MovingEnemies[i]->NextMovementSection;
			MovingEnemies[i]->NextMovementSection = NewMovementSections[i];
		}
	}
	return;
}

ABaseEnemyMovableActor* AEnemyUnitsSpawner::GetFirstValidMovableEnemy(int32 &Index) const
{
	for (int32 i = 0; i < MovingEnemies.Num(); i++)
	{
		if (MovingEnemies[i])
		{
			Index = i;
			return MovingEnemies[i];
		}
	}
	return nullptr;
}

ABaseEnemyMovableActor* AEnemyUnitsSpawner::GetFirstValidMovableEnemy() const
{
	for (int32 i = 0; i < MovingEnemies.Num(); i++)
	{
		if (MovingEnemies[i])
		{
			return MovingEnemies[i];
		}
	}
	return nullptr;
}

// Called every frame
void AEnemyUnitsSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<FVector> DeltaNewMovementLocation;
	CalculateEnemyMoveDeltaLocations(DeltaTime, DeltaNewMovementLocation);
	MoveEnemies(DeltaTime, DeltaNewMovementLocation);


	StaticTurrentSpawnTick();
	FlyingDroneSpawnTick();
}

void AEnemyUnitsSpawner::CalculateEnemyMoveDeltaLocations(const float DeltaTime, TArray<FVector> &DeltaMovementLocations)
{
	for (int32 i = 0; i < MovingEnemies.Num(); i++)
	{
		if (MovingEnemies[i])
		{
			FVector CurrentLocation = MovingEnemies[i]->GetActorLocation();
			FVector NewLocation = CurrentLocation;
			NewLocation.X += ForwardMovementSpeed*DeltaTime;
			if (CurrentLocation.Y > GetLocationFromSection(MovingEnemies[i]->NextMovementSection).Y)
			{
				NewLocation.Y -= SideMovementSpeed*DeltaTime;
			}
			else if (GetLocationFromSection(MovingEnemies[i]->NextMovementSection).Y > CurrentLocation.Y)
			{
				NewLocation.Y += SideMovementSpeed*DeltaTime;
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Null case");
			}
			DeltaMovementLocations.Add(NewLocation);
		}
		else
		{
			DeltaMovementLocations.Add(FVector::ZeroVector);
		}
	}
	int32 Index = 0;
	ABaseEnemyMovableActor* MovableEnemy = GetFirstValidMovableEnemy(Index);
	if (MovableEnemy)
	{
		if (((DeltaMovementLocations[Index].Y - GetLocationFromSection(MovableEnemy->NextMovementSection).Y > 0) && MovementDirection == EMovementDirection::Left) ||
			((DeltaMovementLocations[Index].Y - GetLocationFromSection(MovableEnemy->NextMovementSection).Y < 0) && MovementDirection == EMovementDirection::Right))
		{
			CalculateNextEnemySections();
		}
	}
}

void AEnemyUnitsSpawner::MoveEnemies(const float DeltaTime, const TArray<FVector> &DeltaMovementLocations)
{
	for (int32 i = MovingEnemies.Num() - 1; i >= 0; i--)
	{
		if (MovingEnemies[i])
		{
			if (FMath::Abs(DeltaMovementLocations[i].Y - MovingEnemies[i]->GetActorLocation().Y) == 0)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, FString::SanitizeFloat(MovingEnemies[i]->GetActorLocation().Y));
			}
			MovingEnemies[i]->SetActorLocation(DeltaMovementLocations[i]);
		}
		else
		{
			MovingEnemies.RemoveAt(i);
			if (MovingEnemies.Num() == 0)
			{
				ProcessGameWon();
			}
		}
	}
}

void AEnemyUnitsSpawner::StaticTurrentSpawnTick()
{
	if (PlayerPawn)
	{
		if (PlayerPawn->GetActorLocation().X >= GetLocationFromSection(FMovementSection(StaticTurretNextSpawnSection, 0)).X)
		{
			FMovementSection SpawnSection(StaticTurretSpawnGap + StaticTurretNextSpawnSection, FMath::RandRange(0, (NoOfYSections - 1)));
			SpawnStaticTurret(StaticTurrent1Class, SpawnSection);
			StaticTurretNextSpawnSection += FMath::Max(FMath::RandRange(MinTurrentSpawnDistance, MaxTurrentSpawnDistance), FMath::RandRange(MinTurrentSpawnDistance, MaxTurrentSpawnDistance));
		}
	}
}

void AEnemyUnitsSpawner::SpawnStaticTurret(TSubclassOf<ABaseTurretActor> StaticTurrentClass, FMovementSection SpawnLocation)
{
	ABaseTurretActor* StaticTurrent = GetWorld()->SpawnActor<ABaseTurretActor>(StaticTurrentClass, GetLocationFromSection(SpawnLocation), FRotator(0, 0, 0));
	StaticTurrent->SetLifeSpan(255);
}

void AEnemyUnitsSpawner::FlyingDroneSpawnTick()
{
	if (PlayerPawn)
	{
		if (PlayerPawn->GetActorLocation().X >= GetLocationFromSection(FMovementSection(FlyingDroneNextSpawnSection, 0)).X)
		{
			
			bool bRightSpawn = FMath::RandBool();
			EMovementDirection FlyingDroneMovementDirection;
			if (bRightSpawn)
			{
				FlyingDroneMovementDirection = EMovementDirection::Right;
			}
			else
			{
				FlyingDroneMovementDirection = EMovementDirection::Left;
			}
			int32 FlyingDroneSpawnXSection = FlyingDroneSpawnGap + FlyingDroneNextSpawnSection;

			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "Current Spawn Section = " + FString::FromInt(FlyingDroneSpawnXSection));

			SpawnFlyingDrone(FlyingDroneClass, FlyingDroneMovementDirection, FlyingDroneSpawnXSection);
			FlyingDroneNextSpawnSection += FMath::RandRange(MinFlyingDroneSpawnDistance, MaxFlyingDroneSpawnDistance);

		}
	}
}

const FVector AEnemyUnitsSpawner::GetFlyingSpawnLocation(TSubclassOf<AFlyingDrone> FlyingClass, EMovementDirection _MovementDirection, int32 SpawnXSection) const
{
	AFlyingDrone* TemplateFlyingDrone = Cast<AFlyingDrone>(FlyingClass->GetDefaultObject());
	FVector SpawnLocation(0, 0, 0);
	if (_MovementDirection == EMovementDirection::Right)
	{
		FMovementSection SpawnSection(SpawnXSection, -(TemplateFlyingDrone->YSectionDifference));
		SpawnLocation = GetLocationFromSection(SpawnSection);
	}
	else if (_MovementDirection == EMovementDirection::Left)
	{
		FMovementSection SpawnSection(SpawnXSection, NoOfYSections + (TemplateFlyingDrone->YSectionDifference) - 1);
		SpawnLocation = GetLocationFromSection(SpawnSection);
	}
	SpawnLocation.Z += TemplateFlyingDrone->StartFlightHeight;
	return SpawnLocation;
}

void AEnemyUnitsSpawner::SpawnFlyingDrone(TSubclassOf<AFlyingDrone> FlyingDroneClassClass, EMovementDirection _MovementDirection, int32 XSection)
{
	const FVector SpawnLocation = GetFlyingSpawnLocation(FlyingDroneClassClass, MovementDirection, XSection);
	AFlyingDrone* FlyingDrone = GetWorld()->SpawnActor<AFlyingDrone>(FlyingDroneClassClass, SpawnLocation, FRotator(0, 180, 0));
	FlyingDrone->MovementDirection = MovementDirection;
	FlyingDrone->SideMovementSpeed = SideMovementSpeed*0.6;
	FlyingDrone->ForwardMovementSpeed = ForwardMovementSpeed;
	FlyingDrone->EnemeySpawner = this;
	
	FlyingDrone->PlatformStartYLoc = GetLocationFromSection(FMovementSection(0, 0)).Y;
	FlyingDrone->PlatformEndYLoc = GetLocationFromSection(FMovementSection(0, NoOfYSections - 1)).Y;

	if (_MovementDirection == EMovementDirection::Right)
	{
		FlyingDrone->EndFlyingYLoc = GetLocationFromSection(FMovementSection(0, NoOfYSections + (FlyingDrone->YSectionDifference - 1))).Y;
	}
	else if (_MovementDirection == EMovementDirection::Left)
	{
		FlyingDrone->EndFlyingYLoc = GetLocationFromSection(FMovementSection(0, -(FlyingDrone->YSectionDifference))).Y;
	}

	FlyingDrone->VerticalSpeed = (FlyingDrone->SideMovementSpeed * FlyingDrone->StartFlightHeight) / ((FlyingDrone->YSectionDifference) * LengthOfYSection);
}

const FVector AEnemyUnitsSpawner::GetLocationFromSection(const FMovementSection Section) const
{
	FVector SectionLocation = GetActorLocation();
	SectionLocation.X += LengthOfXSection*Section.XSection;
	SectionLocation.Y += LengthOfYSection*Section.YSection;
	return SectionLocation;
}

const FMovementSection AEnemyUnitsSpawner::GetSectionFromLocation(const FVector Location) const
{
	const FVector OriginLocation = GetLocationFromSection(FMovementSection(0, 0));
	FVector LocationFromOrigin = Location - OriginLocation;
	FMovementSection MovementSection;
	MovementSection.XSection = LocationFromOrigin.X / LengthOfXSection;
	MovementSection.YSection = LocationFromOrigin.Y / LengthOfYSection;
	return MovementSection;
}

void AEnemyUnitsSpawner::ProcessGameWon()
{
	for (TActorIterator<ABaseTurretActor> TurretItr(GetWorld()); TurretItr; ++TurretItr)
	{
		TurretItr->Destroy();
	}
	if (GetWorld()->GetAuthGameMode() && GetWorld()->GetAuthGameMode()->IsA(AIWGameMode::StaticClass()))
	{
		AIWGameMode* GameMode = Cast<AIWGameMode>(GetWorld()->GetAuthGameMode());
		float TimeElasped = GetWorld()->GetTimeSeconds();
		float ScoreCoefficent = GameMode->ScoreTimeCoeffcient;
		GameMode->AddGameScore(FMath::Max(0.f, (240 - TimeElasped) * ScoreCoefficent));
		GameMode->GameWon();
		PlayerPawn->ProcessMenuButton(EMenuOpenType::Won);
		PlayerPawn->bIsGameInProgress = false;
	}
}