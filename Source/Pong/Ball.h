// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBallHitGoalDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBallHitWallDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBallHitPaddleDelegate);

UCLASS()
class PONG_API ABall : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	ABall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable)
    void Start();

    UFUNCTION(BlueprintCallable)
    void Reset();

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed;
    UPROPERTY(EditAnywhere, Category = "Movement")
    float BounceSpeedVariation = 100;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FBallHitGoalDelegate OnBallHitGoalDelegate;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FBallHitWallDelegate OnBallHitWallDelegate;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FBallHitPaddleDelegate OnBallHitPaddleDelegate;
};
