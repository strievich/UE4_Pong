// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PongGameState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScoreUpdatedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMatchStartedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMatchEndedDelegate);
/**
 * 
 */
UCLASS()
class PONG_API APongGameState : public AGameState
{
    GENERATED_BODY()
public:
    void AddScoreP1();
    void AddScoreP2();

    UFUNCTION(BlueprintCallable)
    void ResetScore();

    UFUNCTION(BlueprintCallable)
    int32 GetScoreP1() { return ScoreP1; }
    UFUNCTION(BlueprintCallable)
    int32 GetScoreP2() { return ScoreP2; }

    void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;

    UPROPERTY(EditAnywhere)
    int32 WinScore = 3;
private:
    virtual void HandleMatchHasStarted() override;
    
    UPROPERTY(ReplicatedUsing = OnRep_ScoreP1)
    int32 ScoreP1;
    UPROPERTY(ReplicatedUsing = OnRep_ScoreP2)
    int32 ScoreP2;

    UFUNCTION()
    void OnRep_ScoreP1();
    UFUNCTION()
    void OnRep_ScoreP2();


    UPROPERTY(BlueprintAssignable, Category = "Events")
    FScoreUpdatedDelegate OnScoreUpdatedDelegate;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FMatchStartedDelegate OnMatchStartedDelegate;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FMatchEndedDelegate OnMatchEndedDelegate;
};
