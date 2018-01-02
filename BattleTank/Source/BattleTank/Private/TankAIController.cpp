// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::Tick(float delta)
{
	Super::Tick(delta);

	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(PlayerPawn))
	{
		 return;
	}
	auto PlayerTank = Cast<ATank>(PlayerPawn);
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in cm
		//Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//TODO fire if its ready every Frame
		ControlledTank->Fire(); //TODO limit firing rate

	}

	
}

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();
}

