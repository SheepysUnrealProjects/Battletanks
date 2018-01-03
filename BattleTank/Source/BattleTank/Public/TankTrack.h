// Fill out your copyright notice in the Description page of Project Settings.7

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	
	//Max force per track
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000; //Assume 40,000kg tank, and 1g accelleration
private:
	UTankTrack();
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void ApplySidewaysForce();

	void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Onhit")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void DriveTrack();

	float CurrentThrottle = 0;
};
