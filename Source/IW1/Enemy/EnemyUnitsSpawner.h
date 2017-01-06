// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Player/PlayerPawn.h"
#include "EnemyUnitsSpawner.generated.h"

class ABaseEnemyMovableActor;
class ABaseTurretActor;
class AFlyingDrone;

UENUM(BlueprintType)
enum class EMovementDirection : uint8
{
	Right UMETA(DisplayName = "Right"),
	Left UMETA(DisplayName = "Left"),
	None UMETA(DisplayName = "None")
};

USTRUCT()
struct FMovementSection
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int32 XSection;

	UPROPERTY()
	int32 YSection;

	FMovementSection(int32 NewXSection, int32 NewYSection)
	{
		XSection = NewXSection;
		YSection = NewYSection;
	}

	FMovementSection()
	{
		XSection = 0;
		YSection = 0;
	}

	FMovementSection& operator=(const FMovementSection& Other)
	{
		this->XSection = Other.XSection;
		this->YSection = Other.YSection;

		return *this;
	}

	bool operator==(const FMovementSection& O) const
	{
		return XSection == O.XSection && YSection == O.YSection;
	}
};



UCLASS()
class IW1_API AEnemyUnitsSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyUnitsSpawner();

	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void SpawnInitalEnemies();

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY()
	APlayerPawn* PlayerPawn;
	
//////////////////////////////////////////////
// Dynamic Spawner

	UPROPERTY(EditDefaultsOnly, Category = Sections)
	EMovementDirection MovementDirection;

	UPROPERTY(EditDefaultsOnly, Category = Sections)
	int32 NoOfYSections;

	UPROPERTY(EditDefaultsOnly, Category = Sections)
	float LengthOfXSection;

	UPROPERTY(EditDefaultsOnly, Category = Sections)
	float LengthOfYSection;

	UPROPERTY(EditDefaultsOnly, Category = Sections)
	float ForwardMovementSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Sections)
	float SideMovementSpeed;

	const FVector GetLocationFromSection(const FMovementSection Section) const;

	const FMovementSection GetSectionFromLocation(const FVector Location) const;

	/** temp */
	UPROPERTY(EditDefaultsOnly, Category = MovableUnit)
	TSubclassOf<ABaseEnemyMovableActor> HoverCraftClass;

	UPROPERTY(EditDefaultsOnly, Category = MovableUnit)
	TSubclassOf<ABaseEnemyMovableActor> TankClass;

	UPROPERTY()
	TArray<ABaseEnemyMovableActor*> MovingEnemies;

	void CalculateEnemyMoveDeltaLocations(const float DeltaTime, TArray<FVector> &DeltaMovementLocations);

	void MoveEnemies(const float DeltaTime, const TArray<FVector> &DeltaMovementLocations);

	/** Should be called when an enemy unit has reached its present section */
	void CalculateNextEnemySections();

	ABaseEnemyMovableActor* GetFirstValidMovableEnemy(int32 &Index) const;

	ABaseEnemyMovableActor* GetFirstValidMovableEnemy() const;


//////////////////////////////////////////////
// Static Spawner

	UPROPERTY(EditDefaultsOnly, Category = StaticUnit)
	TSubclassOf<ABaseTurretActor> StaticTurrent1Class;

	UPROPERTY()
	TArray<ABaseTurretActor*> StaticEnemies;
	
	/** in X sections */
	UPROPERTY(EditDefaultsOnly, Category = StaticUnit)
	int32 MaxTurrentSpawnDistance;

	/** in X sections */
	UPROPERTY(EditDefaultsOnly, Category = StaticUnit)
	int32 MinTurrentSpawnDistance;

	/** When the player reaches X = location, it spawns */
	int32 StaticTurretNextSpawnSection;

	/** How much ahead will the static turret spawn */
	int32 StaticTurretSpawnGap;

	void StaticTurrentSpawnTick();

	void SpawnStaticTurret(TSubclassOf<ABaseTurretActor> StaticTurrentClass, FMovementSection SpawnLocation);

//////////////////////////////////////////////
// Flying Spawner

	const FVector GetFlyingSpawnLocation(TSubclassOf<AFlyingDrone> FlyingClass, EMovementDirection MovementDirection, int32 SpawnXSection) const;

	UPROPERTY(EditDefaultsOnly, Category = FlyingUnits)
	TSubclassOf<AFlyingDrone> FlyingDroneClass;

	void SpawnFlyingDrone(TSubclassOf<AFlyingDrone> FlyingDroneClass, EMovementDirection MovementDirection, int32 XSection);

	/** How much ahead will the static turret spawn */
	int32 FlyingDroneSpawnGap;

	int32 FlyingDroneNextSpawnSection;

	void FlyingDroneSpawnTick();

	UPROPERTY(EditDefaultsOnly, Category = FlyingUnits)
	int32 MaxFlyingDroneSpawnDistance;

	/** in X sections */
	UPROPERTY(EditDefaultsOnly, Category = FlyingUnits)
	int32 MinFlyingDroneSpawnDistance;

//////////////////////////////////////////////

	void ProcessGameWon();
};
