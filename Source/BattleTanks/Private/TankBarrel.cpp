// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move the barrel the right amount this frame
	// Given a max elevation speed and the frame time
	auto ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	auto ElevationChange = ClampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewPitchRotation = FMath::Clamp<float>(RelativeRotation.Pitch + ElevationChange, MinElevationDegrees, MaxElevationDegress);

	SetRelativeRotation(FRotator(NewPitchRotation, 0.f, 0.f));

}


