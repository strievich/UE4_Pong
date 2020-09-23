// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuBase.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API UInGameMenu : public UMenuBase
{
	GENERATED_BODY()
protected:
    virtual bool Initialize();
private:
    UPROPERTY(meta = (BindWidget))
    class UButton* ContinueButton;
    UPROPERTY(meta = (BindWidget))
    class UButton* QuitButton;

    UFUNCTION()
    void Continue();

    UFUNCTION()
    void Quit();
};
