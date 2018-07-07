// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto controlledTank = GetControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get controlled Tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Managed to get the controlled tank: %s"), *(controlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("Player Controller ticking..."));
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController HitLocation: %s"), *hitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const
{
	return true;
}

ATank* ATankPlayerController::GetControlledTank() {
	return Cast<ATank>(GetPawn());
}




