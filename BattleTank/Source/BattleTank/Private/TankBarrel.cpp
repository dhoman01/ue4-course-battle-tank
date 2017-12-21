// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankBarrel.h"
#include "Engine.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto NewElevation = FMath::Clamp(RawNewElevation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(NewElevation, 0, 0));
}

