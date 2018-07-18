// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastReloadTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded)
	{
		if (!ProjectileBlueprint) {
			UE_LOG(LogTemp, Error, TEXT("No Projectile Blueprint!"));
		}

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("BarrelLocation")),
			Barrel->GetSocketRotation(FName("BarrelLocation")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastReloadTime = FPlatformTime::Seconds();
	}
}


