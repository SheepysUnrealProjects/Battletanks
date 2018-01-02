// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::Tick(float delta)
{
	Super::Tick(delta);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in cm
	//Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	//TODO make this fire works
	//ControlledTankAimingController->Fire();

	

	
}

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();
}

