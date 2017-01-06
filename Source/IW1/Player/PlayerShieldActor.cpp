j// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "PlayerPawn.h"
#include "PlayerShieldActor.h"


// Sets default values
APlayerShieldActor::APlayerShieldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	if (ArrowComponent)
	{
		ArrowComponent->ArrowColor = FColor(150, 200, 255);
		ArrowComponent->ArrowSize = ArrowComponent->ArrowSize*1.5;
		ArrowComponent->bTreatAsASprite = true;
		ArrowComponent->bIsScreenSizeScaled = true;
		RootComponent = ArrowComponent;
	}

	RightShield = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightShieldMesh"));
	if (RightShield)
	{
		RightShield->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}

	CenterShield = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CenterShieldMesh"));
	if (CenterShield)
	{
		CenterShield->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}

	LeftShield = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftShieldMesh"));
	if (LeftShield)
	{
		LeftShield->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}

	DefenseValueOfShield = 800;
	
}

// Called when the game starts or when spawned
void APlayerShieldActor::BeginPlay()
{
	Super::BeginPlay();

	CurrentShieldDefense.Add(DefenseValueOfShield);//Right
	CurrentShieldDefense.Add(DefenseValueOfShield);//Center
	CurrentShieldDefense.Add(DefenseValueOfShield);//Left
}

void APlayerShieldActor::SetShieldOwner(APlayerPawn* NewPawn)
{
	PlayerPawn = NewPawn;
	SetOwner(PlayerPawn);
}

// Called every frame
void APlayerShieldActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (PlayerPawn)
	{
		float OwnerX = PlayerPawn->GetActorLocation().X;
		FVector NewLocation = GetActorLocation();
		if (OwnerX > NewLocation.X)
		{
			NewLocation.X = OwnerX;
			SetActorLocation(NewLocation);
		}
	}
}

UStaticMeshComponent* APlayerShieldActor::GetShieldMesh(const uint8 ShieldIndex) const
{
	if (ShieldIndex == 0)
	{
		return RightShield;
	}
	else if (ShieldIndex == 1)
	{
		return CenterShield;
	}
	else if (ShieldIndex == 2)
	{
		return LeftShield;
	}
	return nullptr;
}

bool APlayerShieldActor::ShieldTakeDamage(const uint8 ShieldIndex, const float Damage)
{
	if (Damage >= 0)
	{
		CurrentShieldDefense[ShieldIndex] = FMath::Max(0.f, (CurrentShieldDefense[ShieldIndex] - Damage));
		if (CurrentShieldDefense[ShieldIndex] == 0)
		{
			SetShieldVisiblity(ShieldIndex, false);
		}
	}
	else
	{
		if (CurrentShieldDefense[ShieldIndex] == 0)
		{
			SetShieldVisiblity(ShieldIndex, true);
		}
		CurrentShieldDefense[ShieldIndex] = FMath::Min(DefenseValueOfShield, (CurrentShieldDefense[ShieldIndex] - Damage));
	}
	float SizeRatio = CurrentShieldDefense[ShieldIndex] / DefenseValueOfShield;
	UStaticMeshComponent* ShieldMesh = GetShieldMesh(ShieldIndex);
	ShieldMesh->RelativeScale3D.Y = SizeRatio;
	
	return true;
}

void APlayerShieldActor::SetShieldVisiblity(const uint8 ShieldIndex, const bool bVisiblity)
{
	GetShieldMesh(ShieldIndex)->SetVisibility(bVisiblity);
}