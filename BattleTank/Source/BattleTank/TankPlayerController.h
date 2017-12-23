// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //Must be last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	ATank* GetControlledTank() const;

	void BeginPlay() override;
	
	void Tick(float deltaseconds) override;

	//Start the tank moving the barrel so that a shot would be hit
	void AimTowardsCrosshair();

private:
	bool GetLookVectorHitLocation(FVector& OutHitResult, FVector& LookDirection) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;


	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.31;

	float LineTraceRange = 1000000;

	
};
