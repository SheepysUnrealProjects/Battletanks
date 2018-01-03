// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; 
	bWantsBeginPlay = true;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (CurrentAmmo <= 0)
	{
		FiringState = EFiringStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringStatus::Aiming;
	}
	else
	{
		FiringState = EFiringStatus::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) return false;

	auto BarrelForwardVector = Barrel->GetForwardVector();

	return !BarrelForwardVector.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::Initialise(UTankTurret* TurretToSet, UTankBarrel* Barreltoset)
{
	Turret = TurretToSet;
	Barrel = Barreltoset;
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim)
{
	if (!ensure(Barrel)) return;

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		WorldSpaceAim,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);


	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	//If no solution found do nothing
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) 
{
	//Work out difference between current barrel rotation, and aimdirection
	if (!ensure(Barrel) || !ensure(Turret)) return;
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	Barrel->Elevate(DeltaRotator.Pitch); 

	if (DeltaRotator.Yaw > 180 || DeltaRotator.Yaw < -180 )
		Turret->RotateTurret(-DeltaRotator.Yaw);
	else 
		Turret->RotateTurret(DeltaRotator.Yaw);

}


void UTankAimingComponent::Fire()
{
	
	if (FiringState == EFiringStatus::Aiming || FiringState == EFiringStatus::Locked)
	{
		if (!ensure(Barrel && ProjectileBlueprint)) return;
		//Spawn projectile and shot it
		const FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
		const FRotator StartRotation = Barrel->GetSocketRotation(FName("Projectile"));

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, StartLocation, StartRotation);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		CurrentAmmo--;
	}
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int UTankAimingComponent::GetCurrentAmmo() const
{
	return CurrentAmmo;
}
