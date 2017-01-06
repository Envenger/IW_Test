// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "PlayerWeaponComponent.h"
#include "PlayerShieldActor.h"
#include "Player/HUD/IWHUD.h"
#include "PlayerPawn.generated.h"

USTRUCT()
struct FEventFloat
{
	GENERATED_USTRUCT_BODY()

	DECLARE_MULTICAST_DELEGATE_OneParam(FFloatChange, float);
	
private:

	UPROPERTY()
	float FloatValue;

public:

	FFloatChange FloatChangeDelegate;

	const float GetValue() const
	{
		return FloatValue;
	}

	float& operator=(const float& OtherFloat)
	{
		this->FloatValue = OtherFloat;
		FloatChangeDelegate.Broadcast(this->FloatValue);
		return this->FloatValue;
	}

	float& operator+=(const float& OtherFloat)
	{
		this->FloatValue += OtherFloat;
		FloatChangeDelegate.Broadcast(this->FloatValue);
		return this->FloatValue;
	}

	float& operator-=(const float& OtherFloat)
	{
		this->FloatValue -= OtherFloat;
		FloatChangeDelegate.Broadcast(this->FloatValue);
		return this->FloatValue;
	}

	float& operator=(const FEventFloat& OtherEventFloat)
	{
		this->FloatValue = OtherEventFloat.FloatValue;
		FloatChangeDelegate.Broadcast(this->FloatValue);
		return this->FloatValue;
	}

	float& operator+=(const FEventFloat& OtherEventFloat)
	{
		this->FloatValue += OtherEventFloat.FloatValue;
		FloatChangeDelegate.Broadcast(this->FloatValue);
		return this->FloatValue;
	}

	float& operator-=(const FEventFloat& OtherEventFloat)
	{
		this->FloatValue -= OtherEventFloat.FloatValue;
		FloatChangeDelegate.Broadcast(this->FloatValue);
		return this->FloatValue;
	}

	FEventFloat()
	{
		FloatValue = 0;
	}
};


UCLASS()
class IW1_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MeshComponents)
	class UStaticMeshComponent* CenterMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MeshComponents)
	class UStaticMeshComponent* OuterWheel;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MeshComponents)
	class UStaticMeshComponent* LeftHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MeshComponents)
	class UStaticMeshComponent* RightHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WeaponComponents)
	class UPlayerWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* ArrowComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* Camera;

	void SetCameraLocation();
	
//////////////////////////////////////////////////////////
// Movement

	/** An Instance of world is saved to the world wouldn't need to be called everytime */
	UPROPERTY()
	UWorld* World;

	FVector PlayerStartLocation;

	float PlayerStartTime;

	/** Set by the enemy spawner -Y*/
	float MinSideMovementLimit;

	/** Set by the enemy spawner +Y*/
	float MaxSideMovementLimit;

	const float GetMovementSpeed(const float DeltaTime) const;

	float CurrentForwardSpeed;

	float MaxMovementAcceleration;

	FVector CurrentVelocity;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float NormalMovementSpeed;

	float MaxMovementSpeed;

	float MinMovementSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float OuterWheelRadius;

	float OuterWheelCircumference;

	FVector CurrentWheelLocation;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float SideMovementSpeed;

	const bool CheckSideMovement(float AdditionalSideMove) const;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
private:
	void VerticalInput(const float Val);

	float CurrentVerticalInputValue;

	void FireInput();

//////////////////////////////////////////////////
// Shield

	void SpawnShield();

	UPROPERTY(EditDefaultsOnly, Category = ShieldClass)
	TSubclassOf<APlayerShieldActor> ShieldClass;

public:

	UPROPERTY()
	APlayerShieldActor* ShieldActor;

	FEventFloat EventHealth;

	void PlayerHealthChange(const float NewPlayerHealth);

	UPROPERTY(EditDefaultsOnly, Category = Health)
	float MaxPlayerHealth;

//////////////////////////////////////////////////////
// HUD

	bool bIsGameInProgress = true;

	void MenuButtonClicked();

	void ProcessMenuButton(EMenuOpenType MenuOpenType = EMenuOpenType::None);

};
