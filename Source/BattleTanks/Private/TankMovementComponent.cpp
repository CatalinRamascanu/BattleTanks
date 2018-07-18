// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::initialise(UTankTrack* LeftTankTrackToSet, UTankTrack* RightTankTrackToSet)
{
	LeftTankTrack = LeftTankTrackToSet;
	RightTankTrack = RightTankTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float SpeedValue)
{
	if (!LeftTankTrack || !RightTankTrack)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to get both tank tracks"));
		return;
	}
	LeftTankTrack->SetThrottle(SpeedValue);
	RightTankTrack->SetThrottle(SpeedValue);
}
void UTankMovementComponent::IntendMoveLateral(float SpeedValue)
{
	if (!LeftTankTrack || !RightTankTrack)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to get both tank tracks"));
		return;
	}
	LeftTankTrack->SetThrottle(-SpeedValue);
	RightTankTrack->SetThrottle(SpeedValue);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{

	auto AIForwardIntention = MoveVelocity.GetSafeNormal(); // We get the unit vector of the direction the tank it wants to move to
	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForwardDirection);
	IntendMoveForward(ForwardThrow);

	auto LateralThrow = FVector::CrossProduct(AIForwardIntention, TankForwardDirection).Z;
	IntendMoveLateral(LateralThrow);

	UE_LOG(LogTemp, Warning, TEXT("Forward Intent: %f, Lateral Intent: %f"), ForwardThrow, LateralThrow);

}

