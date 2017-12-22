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
	
	void AimAt(FVector HitLocation, float LaunchSpeed);

	bool IsReloading();

	void BeginReload(float ReloadTimeInSeconds);

	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	EFiringState FiringState = EFiringState::Aiming;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float IsMovingTolerance = 0.005f;
	
private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	bool bWasInitialized = false;
	FTimerHandle MyTimerHandle;

	bool MoveBarrelTowards(FVector AimDirection);
	bool MoveTurretTowards(FVector AimDirection);
	
	void EnterAimingState();
};
