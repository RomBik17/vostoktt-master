// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/VTTTableBase.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AVTTTableBase::AVTTTableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Blueprints/Balls/BP_RedBall.BP_RedBall'"));
	if (ItemBlueprint.Object) {
		AvailableToSpawnBalls = (UClass*)ItemBlueprint.Object->GeneratedClass;
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
	i++;
	if (i == 100) Spawn();
}

void AVTTTableBase::Spawn()
{
	UWorld* world = GetWorld();
	if (world)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;

		FRotator rotator;
		FVector spawnLocation = { 0, 0, 170 };

		world->SpawnActor<AVTTBallBase>(AvailableToSpawnBalls, spawnLocation, rotator, spawnParams);
	}
}

