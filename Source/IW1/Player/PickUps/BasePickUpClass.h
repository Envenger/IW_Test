// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Player/PlayerPawn.h"
#include "BasePickUpClass.generated.h"

UCLASS()
class IW1_API ABasePickUpClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickUpClass();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MeshComponents)
	class UStaticMeshComponent* PickUpMesh;

	UPROPERTY(EditdefaultsOnly, Category = PickUp)
	FRotator RotationRate;

	UPROPERTY(EditDefaultsOnly, Category = PickUp)
	int32 Score;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	virtual void PickUpEffect(APlayerPawn* Player){};
	
};
