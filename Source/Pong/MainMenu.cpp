// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "MenuInterface.h"
#include "Components/EditableText.h"

bool UMainMenu::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success) return false;

    HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
    JoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
    CancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
    JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
    QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

    return true;
}

void UMainMenu::HostServer()
{
    if (MenuInterface != nullptr)
    {
        Teardown();
        MenuInterface->Host();
    }
    
}

void UMainMenu::JoinServer()
{
    if (MenuInterface != nullptr)
    {
        Teardown();
        MenuInterface->Join(IPAdressText->GetText().ToString());
    }
    
}

void UMainMenu::OpenJoinMenu()
{
    MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
   MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::QuitGame()
{
    if (MenuInterface != nullptr)
    {
        Teardown();
        MenuInterface->QuitGame();
    }
}

