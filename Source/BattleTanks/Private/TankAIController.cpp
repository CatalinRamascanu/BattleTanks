// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Public/Tank.h"
#include "TankPlayerController.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto controlledTank = Cast<ATank>(GetPawn());
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get AI controlled Tank."));
		return;
	}

	auto playerControlledTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!playerControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get Player Controlled Tank."));
		return;
	}

	MoveToActor(playerControlledTank, AcceptanceRadius);
	
	controlledTank->AimAt(playerControlledTank->GetActorLocation());

	controlledTank->Fire();
}
