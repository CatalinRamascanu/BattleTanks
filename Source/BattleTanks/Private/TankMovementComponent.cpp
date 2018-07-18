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
void UTankMovementComponent::IntendMoveLateral(float SpeedValue)
{
	LeftTankTrack->SetThrottle(-SpeedValue);
	RightTankTrack->SetThrottle(SpeedValue);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	UE_LOG(LogTemp, Warning, TEXT("Tank Wants to Move to %s"), *(MoveVelocity.ToString()));

	auto AIForwardIntention = MoveVelocity.GetSafeNormal(); // We get the unit vector of the direction the tank it wants to move to
	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForwardDirection);
	IntendMoveForward(ForwardThrow);

	auto LateralThrow = FVector::CrossProduct(AIForwardIntention, TankForwardDirection);
	IntendMoveLateral(LateralThrow.Z);
}

