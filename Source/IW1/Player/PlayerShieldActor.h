// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PlayerShieldActor.generated.h"

class APlayerPawn;

UCLASS()
class IW1_API APlayerShieldActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerShieldActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* ArrowComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MeshComponents)
	class UStaticMeshComponent* RightShield;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MeshComponents)
	class UStaticMeshComponent* CenterShield;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MeshComponents)
	class UStaticMeshComponent* LeftShield;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditdefaultsOnly, Category = SheilDefense)
		float DefenseValueOfShield;

	void SetShieldOwner(APlayerPawn* NewPawn);

	UPROPERTY()
		APlayerPawn* PlayerPawn;

	TArray<float> CurrentShieldDefense;

	UStaticMeshComponent* GetShieldMesh(const uint8 ShieldIndex) const;

	bool ShieldTakeDamage(const uint8 ShieldIndex, const float Damage);

	void SetShieldVisiblity(const uint8 ShieldIndex, const bool bVisiblity);

};