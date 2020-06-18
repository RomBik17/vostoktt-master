// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VTTBallBase.generated.h"

class USphereComponent;

UCLASS()
class VOSTOKTT_API AVTTBallBase : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollisionSphere = nullptr;

public:
	// Sets default values for this actor's properties
	AVTTBallBase();

protected:
	// Called when the game starts or when spawned
	virtual void				BeginPlay() override;

	virtual void				ProcessBorderCollision(FVector const& ImpactNormal);
	virtual void				ProcessBallCollision(FVector const& OtherBallLocation, FVector const& OtherBallVelocity, float OtherBallMass);
	virtual void				ProcessBallMovement(float const DeltaTime);
	virtual void				DoCollisionTest(float const DeltaTime);
public:
	// Called every frame
	virtual void				Tick(float DeltaTime) override;

	FORCEINLINE float			GetBallMass() const { return BallMass; }
	FORCEINLINE FVector const& GetBallVelocity() const { return CurrentVelocity; }
	FORCEINLINE void			SetBallVelocity(FVector const& NewVelocity) { CurrentVelocity = NewVelocity; AlreadyCollidedWithBall = true; }

protected:
	UPROPERTY(EditDefaultsOnly)
		float	BallMass = 1.f;

	FVector CurrentVelocity = FVector::ZeroVector;
	bool	AlreadyCollidedWithBall = false;

	int MaxCollisionsWithBorders = 10;
	int MaxCollisionsWithBalls = 10;

	int TemporaryCollisionsWithBorders;
	int TemporaryCollisionsWithBalls;
};
