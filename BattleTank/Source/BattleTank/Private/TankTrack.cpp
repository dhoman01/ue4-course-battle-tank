// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	Throttle = FMath::Clamp(Throttle, -0.5f, 1.0f);
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

