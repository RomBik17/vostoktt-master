// Fill out your copyright notice in the Description page of Project Settings.

#include "..\..\Public\Objects\VTTBlueBall.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include <chrono>

void AVTTBlueBall::movement()
{
	if (canChange)
	{
		canChange = false;

		angle += 1;
		float cs = cos(angle);
		float x;
		float y;
		if (CurrentVelocity.X < 0) x = - CurrentVelocity.Size() * cs;
		else x = CurrentVelocity.Size() * cs;
		if (CurrentVelocity.Y < 0) y = -CurrentVelocity.Size() * sqrt(1 - cs * cs);
		else y = CurrentVelocity.Size() * sqrt(1 - cs * cs);

		SetBallVelocity({ x, y, 0 });
		
		GetWorld()->GetTimerManager().SetTimer(MoveChangeTimerHandle, this, &AVTTBlueBall::resetChanging, 0.1, false);
	}
}

void AVTTBlueBall::resetChanging()
{
	canChange = true;
}

void AVTTBlueBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	movement();
}