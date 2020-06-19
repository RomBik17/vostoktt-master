// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/VTTTableBase.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include <time.h>

// Sets default values
AVTTTableBase::AVTTTableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint> BallBase(TEXT("Blueprint'/Game/Blueprints/Balls/Base/BP_BallBase.BP_BallBase'"));
	if (BallBase.Object) {
		TSubclassOf<AVTTBallBase> temporary;
		temporary = (UClass*)BallBase.Object->GeneratedClass;
		AvailableToSpawnBalls.Push(temporary);
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> RedBall(TEXT("Blueprint'/Game/Blueprints/Balls/BP_RedBall.BP_RedBall'"));
	if (RedBall.Object) {
		TSubclassOf<AVTTBallBase> temporary;
		temporary = (UClass*)RedBall.Object->GeneratedClass;
		AvailableToSpawnBalls.Push(temporary);
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> YellowBall(TEXT("Blueprint'/Game/Blueprints/Balls/BP_YellowBall.BP_YellowBall'"));
	if (YellowBall.Object) {
		TSubclassOf<AVTTBallBase> temporary;
		temporary = (UClass*)YellowBall.Object->GeneratedClass;
		AvailableToSpawnBalls.Push(temporary);
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> BlueBall(TEXT("Blueprint'/Game/Blueprints/Balls/BP_BlueBall.BP_BlueBall'"));
	if (BlueBall.Object) {
		TSubclassOf<AVTTBallBase> temporary;
		temporary = (UClass*)BlueBall.Object->GeneratedClass;
		AvailableToSpawnBalls.Push(temporary);
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> Hamelion(TEXT("Blueprint'/Game/Blueprints/Balls/BP_Hamelion.BP_Hamelion'"));
	if (Hamelion.Object) {
		TSubclassOf<AVTTBallBase> temporary;
		temporary = (UClass*)Hamelion.Object->GeneratedClass;
		AvailableToSpawnBalls.Push(temporary);
	}
}

// Called when the game starts or when spawned
void AVTTTableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVTTTableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Spawn();
}

void AVTTTableBase::Spawn()
{
	if (canSpawn && ballCount < MaxSpawnedBalls)
	{
		canSpawn = false;
		srand(time(0));
		int i = rand() % AvailableToSpawnBalls.Num();
		UWorld* world = GetWorld();
		if (world)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;

			FRotator rotator;
			FVector spawnLocation = { 0, 0, 170 };

			world->SpawnActor<AVTTBallBase>(AvailableToSpawnBalls[i], spawnLocation, rotator, spawnParams);
			ballCount++;
		}

		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AVTTTableBase::resetSpawn, SpawnFrequency, false);
	}
}

void AVTTTableBase::resetSpawn()
{
	canSpawn = true;
}

