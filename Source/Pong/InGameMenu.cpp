// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"
#include "MenuInterface.h"
#include "MenuBase.h"

bool UInGameMenu::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success) return false;

    ContinueButton->OnClicked.AddDynamic(this, &UInGameMenu::Continue);
    QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::Quit);

    return true;
}

void UInGameMenu::Continue()
{
    Teardown();
}

void UInGameMenu::Quit()
{
    if (MenuInterface != nullptr)
    {
        Teardown();
        MenuInterface->GoToMainMenu();
    }
}
