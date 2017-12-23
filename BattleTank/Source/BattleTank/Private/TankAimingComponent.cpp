// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAimingComponent.h"
#include "../Public/Projectile.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"

#include "Engine.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	ensure(BarrelToSet != nullptr && "Did you forget to pass in a Barrel Ref?");
	ensure(TurretToSet != nullptr && "Did you forget to pass in a Turret Ref?");
	bWasInitialized = true;
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	ensure(bWasInitialized && "Did you forget to call Initialize()?");
	if (!Barrel || !Turret) return;

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveTurretTowards(AimDirection);
		MoveBarrelTowards(AimDirection);
		if (!IsReloading())
			FiringState = Barrel->GetForwardVector().Equals(AimDirection, 0.01f) ? EFiringState::Locked : EFiringState::Aiming;
	}
	else if(!IsReloading())
	{
		FiringState = EFiringState::Aiming;
	}
}

bool UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	return !FMath::IsNearlyZero(DeltaRotator.Pitch, IsMovingTolerance);
}

bool UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;

	Turret->Rotate(DeltaRotator.Yaw);
	return !FMath::IsNearlyZero(DeltaRotator.Yaw, IsMovingTolerance);
}

bool UTankAimingComponent::IsReloading()
{
	return FiringState == EFiringState::Reloading;
}

void UTankAimingComponent::Fire()
{
	if (!Barrel || IsReloading()) return;

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile")));
	Projectile->LaunchProjectile(LaunchSpeed);
	BeginReload();
}

void UTankAimingComponent::BeginReload()
{
	FiringState = EFiringState::Reloading;
	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &UTankAimingComponent::EnterAimingState, 1.0f, true, ReloadTimeInSeconds);
}

void UTankAimingComponent::EnterAimingState()
{
	FiringState = EFiringState::Aiming;
	GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);
}

