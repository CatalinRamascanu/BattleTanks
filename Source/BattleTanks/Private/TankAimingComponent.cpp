// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Public/TankAimingComponent.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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

	UE_LOG(LogTemp, Warning, TEXT("%f: Tank aim solution found."), Time);
	auto AimDirection = OutLaunchVelocity.GetSafeNormal();
	
	auto TankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s from %s with speed: %f"), *TankName, *(AimDirection.ToString()), *BarrelLocation, LaunchSpeed);

	MoveBarrelTowardsAimDirection(AimDirection);

}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* component)
{
	Barrel = component;
}

void UTankAimingComponent::MoveBarrelTowardsAimDirection(FVector AimDirection)
{
	// Calculate the difference between the barrel rotation and the aim direction rotation
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation =  AimRotation - BarrelRotation;

	UE_LOG(LogTemp, Warning, TEXT("DeltaRotation Set at: %s"), *(DeltaRotation.ToString()));

	Barrel->Elevate(DeltaRotation.Pitch);
}