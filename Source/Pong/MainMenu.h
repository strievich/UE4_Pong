// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuBase.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API UMainMenu : public UMenuBase
{
    GENERATED_BODY()
protected:
    virtual bool Initialize();

private:
    UPROPERTY(meta = (BindWidget))
    class UButton* HostButton;
    UPROPERTY(meta = (BindWidget))
    class UButton* JoinMenuButton;
    UPROPERTY(meta = (BindWidget))
    class UButton* QuitButton;
    UPROPERTY(meta = (BindWidget))
    class UButton* CancelButton;
    UPROPERTY(meta = (BindWidget))
    class UWidgetSwitcher* MenuSwitcher;
    UPROPERTY(meta = (BindWidget))
    class UWidget* MainMenu;
    UPROPERTY(meta = (BindWidget))
    class UWidget* JoinMenu;
    UPROPERTY(meta = (BindWidget))
    class UButton* JoinButton;
    UPROPERTY(meta = (BindWidget))
    class UEditableText* IPAdressText;

    UFUNCTION()
    void HostServer();
    UFUNCTION()
    void JoinServer();
    UFUNCTION()
    void OpenJoinMenu();
    UFUNCTION()
    void OpenMainMenu();
    UFUNCTION()
    void QuitGame();

};
