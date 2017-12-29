// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//No need to portect points as added at constructon
	Tankaimingcomponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	Tankaimingcomponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetTurret(UTankTurret * BarrelToSet)
{
	Tankaimingcomponent->SetTurret(BarrelToSet);

}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Tankaimingcomponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::Fire()
{
	if (!Barrel) {return;	}
	//Spawn projectile and shot it
	const FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	const FRotator StartRotation = Barrel->GetSocketRotation(FName("Projectile"));

	GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, StartLocation, StartRotation);

	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Tank->Fire() called!"), Time)
}

