// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

// Handle Track properties and methods
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:	
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

private:
	// Force for track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = Input)
	float TrackMaxDrivingForce = 400000.0f; // Assume 40 ton tank w/ 1g acceleration
	
};
