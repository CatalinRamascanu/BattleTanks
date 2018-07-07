// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto controlledTank = getControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get controlled Tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Managed to get the controlled tank: %s"), *(controlledTank->GetName()));
	}
}

ATank* ATankPlayerController::getControlledTank() {
	return Cast<ATank>(GetPawn());
}




