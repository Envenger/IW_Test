// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "Player/PlayerShieldActor.h"
#include "BaseProjectile.h"


// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DumbRoot"));
	if (DummyRoot)
	{
		RootComponent = DummyRoot;
	}

	ProjectileCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ProjectileMesh"));
	if (ProjectileCapsule)
	{
		ProjectileCapsule->SetRelativeRotation(FRotator(90, 0, 0));
		ProjectileCapsule->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	if (ProjectileComponent)
	{
		ProjectileComponent->InitialSpeed = 2200;
	}

	LifeTime = 5;
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeTime);
}

void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (OtherActor->IsA(APlayerShieldActor::StaticClass()))
	{
		APlayerShieldActor* ShieldActor = Cast<APlayerShieldActor>(OtherActor);
		TArray<UPrimitiveComponent*> OverLappingComponents;
		GetOverlappingComponents(OverLappingComponents);
		for (int32 i = 0; i < OverLappingComponents.Num(); i++)
		{
			if (OverLappingComponents[i] == ShieldActor->RightShield)
			{
				if (ShieldActor->CurrentShieldDefense[0] <= 0)
				{
					return;
				}
				ShieldActor->ShieldTakeDamage(0, ProjectileDamage);
			}
			else if (OverLappingComponents[i] == ShieldActor->CenterShield)
			{
				if (ShieldActor->CurrentShieldDefense[1] <= 0)
				{
					return;
				}
				ShieldActor->ShieldTakeDamage(1, ProjectileDamage);
			}
			else if (OverLappingComponents[i] == ShieldActor->LeftShield)
			{
				if (ShieldActor->CurrentShieldDefense[2] <= 0)
				{
					return;
				}
				ShieldActor->ShieldTakeDamage(2, ProjectileDamage);
			}
		}
		Destroy();
	}
}

