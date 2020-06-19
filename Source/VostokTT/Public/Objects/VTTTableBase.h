// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/Array.h"
#include "Objects/VTTBallBase.h"
#include "Objects/VTTRedBall.h"
#include "Objects/VTTYellowBall.h"
#include "Objects/VTTHamelion.h"
#include "Objects/VTTBlueBall.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VTTTableBase.generated.h"

UCLASS()
class VOSTOKTT_API AVTTTableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVTTTableBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float SpawnFrequency = 1;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AVTTBallBase>> AvailableToSpawnBalls;

	UFUNCTION(BlueprintCallable)
	void Spawn();

	int MaxSpawnedBalls = 5;
	int ballCount = 0;

	bool canSpawn = true;
	FTimerHandle SpawnTimerHandle;

	void resetSpawn();
};
