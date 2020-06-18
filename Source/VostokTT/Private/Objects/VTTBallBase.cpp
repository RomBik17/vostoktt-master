// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/VTTBallBase.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include <time.h>

// Sets default values
AVTTBallBase::AVTTBallBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->SetRelativeScale3D(FVector(1.f));

	TemporaryCollisionsWithBalls = 0;
	TemporaryCollisionsWithBorders = 0;

	srand(time(0));
	int positiv_x = rand() % 2;
	int positiv_y = rand() % 2;
	float x;
	float y = rand() % 300 + 2700;
	if (positiv_x) x = rand() % 300 + 2700;
	else x = -(rand() % 300 + 2700);
	if (positiv_y) y = rand() % 300 + 2700;
	else y = -(rand() % 300 + 2700);
	SetBallVelocity({ x, y, 0 });
}

// Called when the game starts or when spawned
void AVTTBallBase::BeginPlay()
{
	Super::BeginPlay();	
}

void AVTTBallBase::ProcessBorderCollision(FVector const& ImpactNormal)
{
	if (ImpactNormal.X > 0 || ImpactNormal.X < 0) SetBallVelocity({ -CurrentVelocity.X, CurrentVelocity.Y, CurrentVelocity.Z });
	else if (ImpactNormal.Y > 0 || ImpactNormal.Y < 0) SetBallVelocity({ CurrentVelocity.X, -CurrentVelocity.Y, CurrentVelocity.Z });
	TemporaryCollisionsWithBorders++;
}

void AVTTBallBase::ProcessBallCollision(FVector const& CollisionImpulseAxis, FVector const& SecondBallVelocity, float SecondBallMass)
{
	
	// This flag is created to prevent multiple collision detection during one logic tick. 
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
	TemporaryCollisionsWithBalls++;
}

void AVTTBallBase::ProcessBallMovement(float const DeltaTime)
{
	SetActorLocation( GetActorLocation() + CurrentVelocity * DeltaTime );
}

void AVTTBallBase::DoCollisionTest(float const DeltaTime)
{
	FVector const& SweepFrom	= GetActorLocation();
	FVector const& SweepTo		= GetActorLocation() + CurrentVelocity * DeltaTime;

	const TArray<AActor*>		ActorsToIgnore({ this });
	
	FHitResult					SweepResult;

	UKismetSystemLibrary::SphereTraceSingle( this, SweepFrom, SweepTo, 
											CollisionSphere->GetScaledSphereRadius(), 
											ETraceTypeQuery::TraceTypeQuery1, 
											false, 
											ActorsToIgnore, 											
											EDrawDebugTrace::None, 
											SweepResult,
											true
											);

	if ( SweepResult.bBlockingHit )
	{	
		if ( AVTTBallBase* Ball = Cast<AVTTBallBase>( SweepResult.GetActor() ) )
		{
			if ( !AlreadyCollidedWithBall )
			{
				FVector FirstBallCachedVelocity		= CurrentVelocity;
				FVector SecondBallCachedVelocity	= Ball->GetBallVelocity();
				float	FirstBallCachedMass			= BallMass;
				float	SecondBallCachedMass		= Ball->GetBallMass();
						
				FVector CollisionImpulseAxis = ( GetActorLocation() - Ball->GetActorLocation() ).GetSafeNormal();
				CollisionImpulseAxis.Z = 0.f;

				this->ProcessBallCollision( CollisionImpulseAxis, SecondBallCachedVelocity, SecondBallCachedMass );
				Ball->ProcessBallCollision( CollisionImpulseAxis, FirstBallCachedVelocity, FirstBallCachedMass );			
			}
		}
		else
			ProcessBorderCollision( SweepResult.ImpactNormal );
	}

	AlreadyCollidedWithBall = false;	
}

// Called every frame
void AVTTBallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DoCollisionTest		( DeltaTime );
	ProcessBallMovement	( DeltaTime );	
}