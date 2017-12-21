// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankMovementComponent.h"
#include "../Public/TankTrack.h"
#include "Engine.h"

void UTankMovementComponent::Initialize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-1 * Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankFowardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	IntendMoveForward(FVector::DotProduct(TankFowardDirection, AIForwardIntention));
	IntendTurnRight(FVector::CrossProduct(TankFowardDirection, AIForwardIntention).Z);
}
