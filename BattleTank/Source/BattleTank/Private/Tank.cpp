// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Projectile.h"
#include "TankBarrel.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


void ATank::BeginPlay() 
{
	Super::BeginPlay();
}

void ATank::Fire()
{
	if (!ensure(Barrel)) return;

	bool isreloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (isreloaded) 
	{
		//Spawn projectile and shot it
		const FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
		const FRotator StartRotation = Barrel->GetSocketRotation(FName("Projectile"));

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, StartLocation, StartRotation);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
	

	
	
}

