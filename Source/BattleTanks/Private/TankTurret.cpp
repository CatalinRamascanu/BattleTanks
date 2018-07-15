// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{

	// Move the turret the right amount this frame
	// Given a max elevation speed and the frame time
	auto ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);

	auto RotationChange = ClampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewYawRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0.f, NewYawRotation,0.f));
}



