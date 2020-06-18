// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/VTTBallBase.h"
#include "VTTBlueBall.generated.h"

/**
 * 
 */
UCLASS()
class VOSTOKTT_API AVTTBlueBall : public AVTTBallBase
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

	void movement();

	void resetChanging();

private:

	bool canChange = true;
	FTimerHandle MoveChangeTimerHandle;
	float angle = 0;
	float time = 0;
};
