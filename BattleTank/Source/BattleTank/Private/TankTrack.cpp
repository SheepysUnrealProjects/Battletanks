// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"



UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}
void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTankTrack::ApplySidewaysForce()
{
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	//Calculate the slippage speed
	auto Slippagespeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	//Work-out the required acceleration this frame to correct
	auto CorrectionAcceleration = -Slippagespeed / DeltaTime * GetRightVector();

	//Calculate and apply sideways (F = m a)
	auto TankRootComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto Correctionforce = (TankRootComponent->GetMass() * CorrectionAcceleration) / 2; //Two tracks
	TankRootComponent->AddForce(Correctionforce);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}