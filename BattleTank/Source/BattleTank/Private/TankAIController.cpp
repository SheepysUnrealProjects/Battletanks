// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::Tick(float delta)
{
	Super::Tick(delta);

	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		 return;
	}
	auto PlayerTank = Cast<ATank>(PlayerPawn);
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		//TODO Move towards the player

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

