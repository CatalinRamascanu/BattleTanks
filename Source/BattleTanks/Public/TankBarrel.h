// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed and +1 is max upward speed
	void Elevate(float RelativeSpeed);

private:

	UPROPERTY(EditAnywhere)
	float MaxDegreesPerSecond = 5.f;

	UPROPERTY(EditAnywhere)
	float MaxElevationDegress = 40.f;

	UPROPERTY(EditAnywhere)
	float MinElevationDegrees = 0.f;
};
