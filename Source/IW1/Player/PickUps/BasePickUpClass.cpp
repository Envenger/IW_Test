// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "Player/PlayerPawn.h"
#include "BasePickUpClass.h"


// Sets default values
ABasePickUpClass::ABasePickUpClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUpMesh"));
	if (PickUpMesh)
	{
		PickUpMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
		RootComponent = PickUpMesh;
	}
	RotationRate = FRotator(0, 65, 0);
	Score = 0;
}

// Called when the game starts or when spawned
void ABasePickUpClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePickUpClass::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	FRotator DeltaRotation = RotationRate*DeltaTime;
	FRotator CurrentRotation = GetActorRotation();
	SetActorRotation(CurrentRotation + DeltaRotation);
}

void ABasePickUpClass::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (OtherActor->IsA(APlayerPawn::StaticClass()))
	{
		PickUpEffect(Cast<APlayerPawn>(OtherActor));
		Destroy();
	}
	
}
