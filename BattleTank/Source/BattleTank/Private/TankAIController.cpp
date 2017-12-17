// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();

	auto Controlledtank = GetControlledTank();
	if (!Controlledtank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController possesing %s"), *(Controlledtank->GetName()));
	}
}

