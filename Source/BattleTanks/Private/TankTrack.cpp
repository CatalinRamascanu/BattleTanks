// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float ThrottleSpeed)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Error, TEXT("%s : Track throttling at %f ..."), *Name,  ThrottleSpeed);

	auto ForceApplied = GetForwardVector() * ThrottleSpeed * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

