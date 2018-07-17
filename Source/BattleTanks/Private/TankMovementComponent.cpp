// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::initialise(UTankTrack* LeftTankTrackToSet, UTankTrack* RightTankTrackToSet)
{
	if (!LeftTankTrackToSet || !RightTankTrackToSet)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to get both tank tracks"));
		return;
	}
	LeftTankTrack = LeftTankTrackToSet;
	RightTankTrack = RightTankTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float SpeedValue)
{
	LeftTankTrack->SetThrottle(SpeedValue);
	RightTankTrack->SetThrottle(SpeedValue);
}
void UTankMovementComponent::IntendMoveBackwards(float SpeedValue)
{
	LeftTankTrack->SetThrottle(SpeedValue);
	RightTankTrack->SetThrottle(SpeedValue);
}


