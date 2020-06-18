// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/VTTBallBase.h"
#include "VTTRedBall.generated.h"

/**
 * 
 */
UCLASS()
class VOSTOKTT_API AVTTRedBall : public AVTTBallBase
{
	GENERATED_BODY()
	
public:

	int MaxMass = 20;

protected:

	virtual void ProcessBallCollision( FVector const& OtherBallLocation, FVector const& OtherBallVelocity, float OtherBallMass ) override;

};
