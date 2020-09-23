// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameState.h"
#include <Net/UnrealNetwork.h>

void APongGameState::AddScoreP1()
{
    if (GetLocalRole() == ROLE_Authority)
    {
        ScoreP1++;

        OnRep_ScoreP1();
    }
}

void APongGameState::AddScoreP2()
{
    if (GetLocalRole() == ROLE_Authority)
    {
        ScoreP2++;

        OnRep_ScoreP2();
    }
}

void APongGameState::ResetScore()
{
    if (GetLocalRole() == ROLE_Authority)
    {
        ScoreP1 = 0;
        ScoreP2 = 0;
        OnRep_ScoreP1();
        OnRep_ScoreP2();
    }
}

void APongGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APongGameState, ScoreP1);
    DOREPLIFETIME(APongGameState, ScoreP2);
}

void APongGameState::HandleMatchHasStarted()
{
    ResetScore();
    OnMatchStartedDelegate.Broadcast();
}


void APongGameState::OnRep_ScoreP1()
{
    UE_LOG(LogTemp, Warning, TEXT("ScoreP1 replicated"));
    OnScoreUpdatedDelegate.Broadcast();
    if (ScoreP1 == WinScore)
    {
        OnMatchEndedDelegate.Broadcast();
    }
}
void APongGameState::OnRep_ScoreP2()
{
    UE_LOG(LogTemp, Warning, TEXT("ScoreP2 replicated"));
    OnScoreUpdatedDelegate.Broadcast();
    if (ScoreP2 == WinScore)
    {
        OnMatchEndedDelegate.Broadcast();
    }
}