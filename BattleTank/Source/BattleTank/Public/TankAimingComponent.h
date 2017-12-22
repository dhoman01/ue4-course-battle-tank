// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM(BlueprintType)
enum class EFiringState : uint8
{
	Reloading = 0,
	Aiming = 1,
	Locked = 2
};

class AProjectile;
class UTankBarrel;
class UTankTurret;

// Class to handle aiming delegation
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();
	
	void AimAt(FVector HitLocation);

	bool IsReloading();


	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	EFiringState FiringState = EFiringState::Aiming;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float IsMovingTolerance = 0.005f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 8000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;
	
private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	bool bWasInitialized = false;
	FTimerHandle MyTimerHandle;

	bool MoveBarrelTowards(FVector AimDirection);
	bool MoveTurretTowards(FVector AimDirection);
	
	void BeginReload();
	void EnterAimingState();
};
