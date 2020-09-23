// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuInterface.h"
#include "PongGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API UPongGameInstance : public UGameInstance, public IMenuInterface
{
    GENERATED_BODY()

public:
    UPongGameInstance(const FObjectInitializer & ObjectInitializer);

    virtual void Init();

    UFUNCTION(Exec)
    void Host() override;

    UFUNCTION(Exec)
    void Join(const FString& Adress) override;

    UFUNCTION(BlueprintCallable)
    void LoadMenu();

    UFUNCTION(BlueprintCallable)
    void LoadInGameMenu();

    UFUNCTION()
    void GoToMainMenu() override;

    UFUNCTION()
    void QuitGame() override;


private:
    TSubclassOf<class UUserWidget> MenuClass;
    TSubclassOf<class UUserWidget> InGameMenuClass;

    class UMainMenu* Menu;
    class UInGameMenu* InGameMenu;
};
