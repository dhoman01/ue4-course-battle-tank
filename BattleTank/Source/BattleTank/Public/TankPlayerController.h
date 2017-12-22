// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be last include

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float CrossHairYLocation = 0.33f;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	int32 LineTraceRange = 1000000; // KM

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

private:
	virtual void Tick(float DeltaTime) override;
	
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;
};
