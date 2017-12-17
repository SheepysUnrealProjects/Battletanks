// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		return nullptr;
	}

	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();

	auto player = GetPlayerTank();
	auto Controlledtank = GetControlledTank();
	if (!Controlledtank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController possesing %s"), *(Controlledtank->GetName()));
	}
	
	if (!player)
	{
		UE_LOG(LogTemp, Warning, TEXT("No player found"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player: %s"), *(player->GetName()));
	}

}
