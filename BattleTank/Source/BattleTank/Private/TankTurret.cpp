// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"



void UTankTurret::RotateTurret(float RelativeSpeed)
{

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed * MaxDegPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotaion = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, RawNewRotaion, 0));
}
