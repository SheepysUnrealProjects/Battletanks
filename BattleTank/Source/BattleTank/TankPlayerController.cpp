// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto Controlledtank = GetControlledTank();
	if (!Controlledtank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing %s"), *(Controlledtank->GetName()));
	}
}

void ATankPlayerController::Tick(float deltaseconds)
{
	Super::Tick(deltaseconds);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() 
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //out parameter
	
	if (GetSightRayHitLocation(HitLocation)) //has side effect, is going to line trace
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
			// TODO Tell controlled tank to aim at this point
	}

	
}

// Get world location of linetrace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//Find crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	//"De-project" the screen position of the crosshair to a world direction
	//Line-trace along that look direction, and see what we hit(up to max range)
	return true;
}
