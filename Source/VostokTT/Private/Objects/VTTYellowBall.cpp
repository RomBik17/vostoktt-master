// Fill out your copyright notice in the Description page of Project Settings.

#include "..\..\Public\Objects\VTTYellowBall.h"
#include <time.h>

void AVTTYellowBall::ProcessBorderCollision(FVector const& ImpactNormal)
{
	if (ImpactNormal.X > 0)
	{
		srand(time(0));
		float coef = rand() % 7 / 10 + 0.2;
		float x = CurrentVelocity.Size() * coef;
		float y = CurrentVelocity.Size() * (1 - coef);
		SetBallVelocity({ x, y, 0 });
	}
	else if (ImpactNormal.Y > 0)
	{
		srand(time(0));
		float coef = rand() % 7 / 10 + 0.2;
		float y = CurrentVelocity.Size() * coef;
		float x = CurrentVelocity.Size() * (1 - coef);
		SetBallVelocity({ x, y, 0 });
	}
	else if (ImpactNormal.X < 0) 
	{
		srand(time(0));
		float coef = rand() % 7 / 10 + 0.2;
		float x = -CurrentVelocity.Size() * coef;
		float y = CurrentVelocity.Size() * (1 - coef);
		SetBallVelocity({ x, y, 0 });
	}
	else if (ImpactNormal.Y < 0)
	{
		srand(time(0));
		float coef = rand() % 7 / 10 + 0.2;
		float y = - CurrentVelocity.Size() * coef;
		float x = CurrentVelocity.Size() * (1 - coef);
		SetBallVelocity({ x, y, 0 });
	}
	TemporaryCollisionsWithBorders++;
}

