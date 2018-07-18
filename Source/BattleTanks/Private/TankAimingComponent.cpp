// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAimingComponent.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("BarrelLocation"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	auto Time = GetWorld()->GetTimeSeconds();

	if (!bHaveAimSolution)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f: Tank aim solution NOT found."), Time);
		return;
	}

	auto AimDirection = OutLaunchVelocity.GetSafeNormal();
	
	auto TankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s from %s with speed: %f"), *TankName, *(AimDirection.ToString()), *BarrelLocation, LaunchSpeed);

	MoveBarrelTowardsAimDirection(AimDirection);

}

void UTankAimingComponent::MoveBarrelTowardsAimDirection(FVector AimDirection)
{
	if (!Barrel || !Turret) { return; }
	
	auto AimRotation = AimDirection.Rotation();

	// Calculate the difference between the barrel rotation and the aim direction rotation
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto BarrelDeltaRotation =  AimRotation - BarrelRotation;

	Barrel->Elevate(BarrelDeltaRotation.Pitch);

	// Calculate the difference between the Turret rotation and the aim direction rotation
	auto TurretRotation = Turret->GetForwardVector().Rotation();
	auto TurretDeltaRotation = AimRotation - TurretRotation;

	Turret->Rotate(TurretDeltaRotation.Yaw);
}