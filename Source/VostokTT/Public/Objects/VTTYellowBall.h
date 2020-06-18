// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/VTTBallBase.h"
#include "VTTYellowBall.generated.h"

/**
 * 
 */
UCLASS()
class VOSTOKTT_API AVTTYellowBall : public AVTTBallBase
{
	GENERATED_BODY()
	virtual void ProcessBorderCollision(FVector const& ImpactNormal) override;
};
