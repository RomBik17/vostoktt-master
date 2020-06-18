// Fill out your copyright notice in the Description page of Project Settings.

#include "..\..\Public\Objects\VTTRedBall.h"

void AVTTRedBall::ProcessBallCollision(FVector const& CollisionImpulseAxis, FVector const& SecondBallVelocity, float SecondBallMass)
{
	AlreadyCollidedWithBall = true;
	float cst1 = CurrentVelocity.X / CurrentVelocity.Size();
	float snt1 = CurrentVelocity.Y / CurrentVelocity.Size();
	float cst2 = SecondBallVelocity.X / SecondBallVelocity.Size();
	float snt2 = SecondBallVelocity.Y / SecondBallVelocity.Size();
	float cs = CollisionImpulseAxis.X / CollisionImpulseAxis.Size();
	float sn = CollisionImpulseAxis.Y / CollisionImpulseAxis.Size();
	float x1 = (CurrentVelocity.Size() * (cst1 * cs + snt1 * sn) * (BallMass - SecondBallMass) + 2 * SecondBallMass * SecondBallVelocity.Size() * (cst2 * cs + snt2 * sn)) / (BallMass + SecondBallMass) * cs + CurrentVelocity.Size() * (snt1 * cs - cst1 * sn) * (-sn);
	float y1 = (CurrentVelocity.Size() * (cst1 * cs + snt1 * sn) * (BallMass - SecondBallMass) + 2 * SecondBallMass * SecondBallVelocity.Size() * (cst2 * cs + snt2 * sn)) / (BallMass + SecondBallMass) * sn + CurrentVelocity.Size() * (snt1 * cs - cst1 * sn) * (cs);
	SetBallVelocity({ x1, y1, 0 });;
	BallMass += SecondBallMass;
	TemporaryCollisionsWithBalls++;
}

