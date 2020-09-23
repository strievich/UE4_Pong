// Fill out your copyright notice in the Description page of Project Settings.

#include "Paddle.h"
#include "Components/StaticMeshComponent.h"
#include <Net/UnrealNetwork.h>

// Sets default values
APaddle::APaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();
	
    if (HasAuthority())
    {
        //NetUpdateFrequency = 5;
    }
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentPosition = GetActorLocation();
    FVector MoveDirection = FVector(0.0f, Speed, 0.0f);
    CurrentPosition += MoveDirection * DeltaTime;
	CurrentPosition.Y = FMath::Clamp(CurrentPosition.Y, UpperBound, LowerBound);
	SetActorLocation(CurrentPosition);
    if (HasAuthority())
    {
        ReplicatedLocation = CurrentPosition;
    }
}

// Called to bind functionality to input
void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("Move", this, &APaddle::Move);
}

void APaddle::Move(float AxisValue)
{
    Speed = AxisValue * MaxSpeed;
    Server_Move(AxisValue);
}

void APaddle::OnRep_ReplicatedLocation()
{
    UE_LOG(LogTemp, Warning, TEXT("Replicated"));
    SetActorLocation(ReplicatedLocation);
}

void APaddle::Server_Move_Implementation(float AxisValue)
{
    Speed = AxisValue * MaxSpeed;
}

bool APaddle::Server_Move_Validate(float AxisValue)
{
    return true;
}

void APaddle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    DOREPLIFETIME(APaddle, ReplicatedLocation);
    DOREPLIFETIME(APaddle, Speed);
}