// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h" // Leave as last include

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// How close can AI Tank get to player
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 3000.0f;
	
};
