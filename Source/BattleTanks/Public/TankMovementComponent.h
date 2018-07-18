// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tracks of a tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void IntendMoveForward(float SpeedValue);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void IntendMoveLateral(float SpeedValue);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void initialise(UTankTrack* LeftTankTrackToSet, UTankTrack* RightTankTrackToSet);

	
private:
	UTankTrack * LeftTankTrack = nullptr;
	UTankTrack * RightTankTrack = nullptr;

	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
