// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Paddle.generated.h"

UCLASS()
class PONG_API APaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APaddle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION()
    float GetCurrentSpeed() { return Speed; }
private:
	void Move(float AxisValue);
    UFUNCTION(Server, Reliable, WithValidation)
    void Server_Move(float AxisValue);

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* Mesh;
	

	UPROPERTY(EditAnywhere, Category = "Boundary")
	float UpperBound = -420;
	UPROPERTY(EditAnywhere, Category = "Boundary")
	float LowerBound = 420;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float MaxSpeed = 1000;
    UPROPERTY(EditAnywhere, Category = "Movement")
    float Acceleration = 1000;
    UPROPERTY(EditAnywhere, Category = "Movement")
    float Drag = 100;

    UPROPERTY(Replicated)
    float Speed = 0;

    UPROPERTY(ReplicatedUsing= OnRep_ReplicatedLocation)
    FVector ReplicatedLocation;

    UFUNCTION()
    void OnRep_ReplicatedLocation();
};
