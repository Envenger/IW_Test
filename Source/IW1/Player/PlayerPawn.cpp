// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "Enemy/StaticTurret/BaseTurretActor.h"
#include "Enemy/EnemyUnitsSpawner.h"
#include "Enemy/BaseEnemyActor.h"
#include "PlayerShieldActor.h"
#include "Player/PlayerWeaponComponent.h"
#include "IWGameMode.h"
#include "Player/HUD/IWHUD.h"
#include "PlayerPawn.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CenterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CenterMesh"));
	if (CenterMesh)
	{
		RootComponent = CenterMesh;
		CenterMesh->SetSimulatePhysics(true);
		CenterMesh->bLightAttachmentsAsGroup = true;
	}

	OuterWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OuterWheel"));
	if (OuterWheel)
	{
		OuterWheel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}

	RightHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightHand"));
	if (RightHand)
	{
		RightHand->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}

	LeftHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftHand"));
	if (LeftHand)
	{
		LeftHand->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}

	WeaponComponent = CreateDefaultSubobject<UPlayerWeaponComponent>(TEXT("WeaponComp"));
	if (WeaponComponent)
	{
		WeaponComponent->RightHand = RightHand;
		WeaponComponent->LeftHand = LeftHand;
	}

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	if (ArrowComponent)
	{
		ArrowComponent->ArrowColor = FColor(150, 200, 255);
		ArrowComponent->ArrowSize = ArrowComponent->ArrowSize*1.5;
		ArrowComponent->bTreatAsASprite = true;
		ArrowComponent->bIsScreenSizeScaled = true;
		ArrowComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	if (SpringArm)
	{
		SpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		SpringArm->TargetArmLength = 160.0f; // The camera follows at this distance behind the character	
		SpringArm->SocketOffset = FVector(0.f, 0.f, 60.f);
		SpringArm->bEnableCameraLag = false;
		SpringArm->CameraLagSpeed = 15.f;
		SpringArm->bDoCollisionTest = false;
		SpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	if (Camera)
	{
		Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
		Camera->bUsePawnControlRotation = false; // Don't rotate camera with controller
	}

	CurrentVerticalInputValue = 0;
	
	MaxMovementAcceleration = 5;

	NormalMovementSpeed = 450;
	MaxMovementSpeed = 500;
	MinMovementSpeed = 400;

	SideMovementSpeed = 400;

	MinSideMovementLimit = -99999;
	MaxSideMovementLimit = 99999;

	OuterWheelRadius = 68.2;

	MaxPlayerHealth = 100;
	
	PlayerStartTime = 0;

	CurrentForwardSpeed = NormalMovementSpeed;

	CurrentVelocity = FVector::ZeroVector;

	EventHealth.FloatChangeDelegate.AddUObject(this, &APlayerPawn::PlayerHealthChange);
}


// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	EventHealth = MaxPlayerHealth;

	World = GetWorld();
	PlayerStartTime = World->GetTimeSeconds();

	PlayerStartLocation = CenterMesh->GetComponentLocation();// GetActorLocation();

	CurrentWheelLocation = PlayerStartLocation;
	CurrentWheelLocation.Y = 0;
	OuterWheelCircumference = 2 * PI * OuterWheelRadius * 1.15;

	for (TActorIterator<AEnemyUnitsSpawner> EnemySpawnItr(GetWorld()); EnemySpawnItr; ++EnemySpawnItr)
	{
		EnemySpawnItr->PlayerPawn = this;
		EnemySpawnItr->SpawnInitalEnemies();

		MinSideMovementLimit = EnemySpawnItr->GetLocationFromSection(FMovementSection(0, 0)).Y;
		MaxSideMovementLimit = EnemySpawnItr->GetLocationFromSection(FMovementSection(0, EnemySpawnItr->NoOfYSections - 1)).Y;
	}

	for (TActorIterator<ABaseTurretActor> TurretItr(GetWorld()); TurretItr; ++TurretItr)
	{
		TurretItr->PlayerActor = this;
	}

	SpawnShield();
}

void APlayerPawn::SpawnShield()
{
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	ShieldActor = GetWorld()->SpawnActor<APlayerShieldActor>(ShieldClass, SpawnLocation, SpawnRotation);
	ShieldActor->SetShieldOwner(this);
}

// Called every frame
void APlayerPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	CurrentVelocity.X = CurrentForwardSpeed;

	CurrentVelocity.Y = SideMovementSpeed*CurrentVerticalInputValue;
	if (!CheckSideMovement(DeltaTime * CurrentVelocity.Y))
	{
		CurrentVelocity.Y = 0;
	}

	FVector CurrentActorLocation = GetActorLocation();
	CurrentActorLocation += CurrentVelocity* DeltaTime;
	SetActorLocation(CurrentActorLocation);

	CurrentForwardSpeed = GetMovementSpeed(DeltaTime);
	FVector NewWheelLocation = GetActorLocation();
	NewWheelLocation.Y = 0;// Ignores Side movements;
	FVector Motion = NewWheelLocation - CurrentWheelLocation;
	float DeltaMovement = Motion.Size();
	CurrentWheelLocation = NewWheelLocation;

	float DeltaOuterWheelRotation = DeltaMovement / OuterWheelCircumference * 360;
	OuterWheel->AddLocalRotation(FRotator(-DeltaOuterWheelRotation, 0, 0));

	CenterMesh->SetPhysicsAngularVelocity(FVector(0, 0, 0));
	SetActorRotation(FRotator(0, 0, 0));
}

const bool APlayerPawn::CheckSideMovement(float AdditionalSideMove) const
{
	float NewPawnY = GetActorLocation().Y + AdditionalSideMove;
	if (NewPawnY > MaxSideMovementLimit || NewPawnY < MinSideMovementLimit)
	{
		return false;
	}
	return true;
}

void APlayerPawn::SetCameraLocation()
{
	FVector PlayerLocation = GetActorLocation();
	FVector LocationDifference = PlayerStartLocation - PlayerLocation;
	SpringArm->RelativeLocation.Y = LocationDifference.Y;
}

const float APlayerPawn::GetMovementSpeed(const float DeltaTime) const
{
	float CurrentTime = World->GetTimeSeconds();
	float CalculatedDistanceTraveled = (CurrentTime - PlayerStartTime)*NormalMovementSpeed;
	float CurrentDistanceTraveled = (GetActorLocation().X - PlayerStartLocation.X);
	
	float DistanceTraveledDifference = CalculatedDistanceTraveled - CurrentDistanceTraveled;
	if (DistanceTraveledDifference > 0)
	{
		return FMath::FInterpTo(CurrentForwardSpeed, MaxMovementSpeed, DeltaTime, MaxMovementAcceleration);
	}
	else if (DistanceTraveledDifference < 0)
	{
		return FMath::FInterpTo(CurrentForwardSpeed, MinMovementSpeed, DeltaTime, MaxMovementAcceleration);
	}
	else
	{
		return FMath::FInterpTo(CurrentForwardSpeed, NormalMovementSpeed, DeltaTime, MaxMovementAcceleration);
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerPawn::VerticalInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerPawn::FireInput);

	FInputActionBinding& toggle = PlayerInputComponent->BindAction("Menu", IE_Pressed, this, &APlayerPawn::MenuButtonClicked);
	toggle.bExecuteWhenPaused = true;
}

void APlayerPawn::VerticalInput(const float Val)
{
	if (!FMath::IsNearlyEqual(Val, 0.f))
	{
		CurrentVerticalInputValue = Val;
	}
	else
	{
		CurrentVerticalInputValue = 0;
	}
}

void APlayerPawn::FireInput()
{
	WeaponComponent->ProcessWeaponFire();
}

void APlayerPawn::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (OtherActor->IsA(ABaseEnemyActor::StaticClass()))
	{
		ABaseEnemyActor* EnemyActor = Cast<ABaseEnemyActor>(OtherActor);
		if (EnemyActor->bIsStompable)
		{
			AIWGameMode* GameMode = Cast<AIWGameMode>(GetWorld()->GetAuthGameMode());
			GameMode->AddGameScore(60);
			EnemyActor->DestroyUnit(true);
		}
	}
}

void APlayerPawn::MenuButtonClicked()
{
	ProcessMenuButton(EMenuOpenType::None);
}

void APlayerPawn::ProcessMenuButton(EMenuOpenType MenuOpenType)
{
	if (GetController() && GetController()->IsA(APlayerController::StaticClass()))
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		if (PC->GetHUD() && PC->GetHUD()->IsA(AIWHUD::StaticClass()))
		{
			AIWHUD* HUD = Cast<AIWHUD>(PC->GetHUD());
			if (HUD->bIsMenuOpen)
			{
				if (bIsGameInProgress)
				{
					UGameplayStatics::SetGamePaused(this, false);
					PC->bShowMouseCursor = false;
					HUD->CloseMenu();
				}
			}
			else
			{
				if (bIsGameInProgress)
				{
					UGameplayStatics::SetGamePaused(this, true);
					PC->bShowMouseCursor = true;
					HUD->OpenMenu(MenuOpenType);
				}
			}
		}
	}
}

void APlayerPawn::PlayerHealthChange(const float NewPlayerHealth)
{
	if (NewPlayerHealth < 0)
	{
		if (GetWorld()->GetAuthGameMode() && GetWorld()->GetAuthGameMode()->IsA(AIWGameMode::StaticClass()))
		{
			ProcessMenuButton(EMenuOpenType::Lost);
			bIsGameInProgress = false;
		}
	}
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC->GetHUD() && PC->GetHUD()->IsA(AIWHUD::StaticClass()))
	{
		AIWHUD* HUD = Cast<AIWHUD>(PC->GetHUD());
		float NewLifeRatio = (EventHealth.GetValue() / MaxPlayerHealth) - 0.001;
		if (HUD->HealthBarMaterialD)
		{
			HUD->HealthBarMaterialD->SetScalarParameterValue("LifeRatio", NewLifeRatio);
		}
	}
}

