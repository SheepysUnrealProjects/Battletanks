// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTracktoset, UTankTrack* Righttracktoset)
{
	
	LeftTrack = LeftTracktoset;
	RightTrack = Righttracktoset;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntenion = MoveVelocity.GetSafeNormal();
	
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntenion);
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntenion).Z;
	
	IntendMoveForward(ForwardThrow);

	IntendTurnright(RightThrow);
	//UE_LOG(LogTemp, Warning, TEXT("Right: %f, Forward: %f"), ForwardThrow, RightThrow)
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	//TODO prevent double-speed due to dual
}

void UTankMovementComponent::IntendTurnright(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	//TODO prevent double-speed due to dual
}