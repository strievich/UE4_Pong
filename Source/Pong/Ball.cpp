// Fill out your copyright notice in the Description page of Project Settings.
#include "Ball.h"
#include "Components/StaticMeshComponent.h"
#include "Paddle.h"
#include "Bounding.h"
#include "Goal.h"
#include "PongGameState.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ABall::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABall::Start()
{
    const FVector Velocity = FVector(Speed, 0.0f, 0.0f);
    Mesh->SetPhysicsLinearVelocity(Velocity);
}

void ABall::Reset()
{
    SetActorLocation(FVector::ZeroVector);
    Mesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
}

void ABall::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APaddle* Paddle = Cast<APaddle>(OtherActor);
	if (IsValid(Paddle))
	{
		//mirror by x
		FVector BallVelocity = GetVelocity();
        FVector PaddlePosition = Paddle->GetActorLocation();
        if (FMath::Sign(BallVelocity.X) == FMath::Sign(PaddlePosition.X)) //hack to prevent multiple direction change by paddle side 
        {
            BallVelocity.X = -BallVelocity.X;
            float PaddleSpeed = Paddle->GetCurrentSpeed();
            if (FMath::Abs(PaddleSpeed) > 0)
            {
                BallVelocity.Y = PaddleSpeed;
            }
            BallVelocity.Y += FMath::RandRange(-BounceSpeedVariation, BounceSpeedVariation);
            Mesh->SetPhysicsLinearVelocity(BallVelocity);

        }
        OnBallHitPaddleDelegate.Broadcast();
	}
	
	ABounding* Bounding = Cast<ABounding>(OtherActor);
	if (IsValid(Bounding))
	{
		//mirror by y
		FVector Velocity = GetVelocity();
		Velocity.Y = -Velocity.Y;
		Mesh->SetPhysicsLinearVelocity(Velocity);
        OnBallHitWallDelegate.Broadcast();
	}

	AGoal* Goal = Cast<AGoal>(OtherActor);
	if (IsValid(Goal))
	{
		SetActorLocation(FVector(0.0f, 0.0f, 0.0f));
		FVector GoalPosition = OtherActor->GetActorLocation();
		const FVector Velocity = FVector(Speed * FMath::Sign(-GoalPosition.X), 0.0f, 0.0f);
		Mesh->SetPhysicsLinearVelocity(Velocity);

        APongGameState* const GameState = GetWorld() != NULL ? GetWorld()->GetGameState<APongGameState>() : NULL;
        
        if (Goal->ActorHasTag(TEXT("P1")))
        {
            GameState->AddScoreP1();
            OnBallHitGoalDelegate.Broadcast();
        }
        if (Goal->ActorHasTag(TEXT("P2")))
        {
            GameState->AddScoreP2();
            OnBallHitGoalDelegate.Broadcast();
        }
		
	}
}

