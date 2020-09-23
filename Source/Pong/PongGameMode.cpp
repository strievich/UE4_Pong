// Copyright Epic Games, Inc. All Rights Reserved.


#include "PongGameMode.h"
#include <GameFramework/Controller.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/PlayerState.h>

void APongGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	Count++;
	UE_LOG(LogTemp, Warning, TEXT("Player joined:%i"), Count);
    FString PlayerName = FString::Printf(TEXT("P%d"), Count);
    NewPlayer->PlayerState->SetPlayerName(PlayerName);
}

// APongGameMode::FindPlayerStart(AController* Player, const FString& IncomingName /* = TEXT("") */)
// {
//     return nullptr;
// }

// bool APongGameMode::ReadyToStartMatch_Implementation()
// {
// 	
// 	return Super::ReadyToStartMatch()
//         &&MaxNumPlayers == NumPlayers;
// 
// }

void APongGameMode::BeginPlay()
{
	Super::BeginPlay();

}
