// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "TankPlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto controlledTank = getControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get AI controlled Tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Managed to get the AI controlled tank: %s"), *(controlledTank->GetName()));
	}

	auto playerControlledTank = getPlayerControlledTank();
	if (!playerControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get Player Controlled Tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Managed to get the Player controlled tank: %s"), *(playerControlledTank->GetName()));
	}
}

ATank* ATankAIController::getControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::getPlayerControlledTank() const
{
	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerTank)
	{
		return nullptr;
	}

	return Cast<ATank>(playerTank);

}
