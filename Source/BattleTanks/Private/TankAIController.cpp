// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "TankPlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto controlledTank = GetControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get AI controlled Tank."));
		return;
	}

	auto playerControlledTank = GetPlayerControlledTank();
	if (!playerControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get Player Controlled Tank."));
		return;
	}
	
	controlledTank->AimAt(playerControlledTank->GetActorLocation());
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerControlledTank() const
{
	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerTank)
	{
		return nullptr;
	}

	return Cast<ATank>(playerTank);

}
