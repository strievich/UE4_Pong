// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PongGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APongGameMode : public AGameMode
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    int32 GetPlayersCount() { return Count; }
protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;

    //virtual AActor * FindPlayerStart(AController* Player, const FString& IncomingName /* = TEXT("") */) override;
	

	//bool ReadyToStartMatch_Implementation() override;

	void BeginPlay() override;

	int32 Count = 0;
	int32 MaxNumPlayers = 2;

};
