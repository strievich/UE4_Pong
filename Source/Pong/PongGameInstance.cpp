// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameInstance.h"
#include "MainMenu.h"
#include "InGameMenu.h"
#include "MenuBase.h"
#include <Blueprint/UserWidget.h>

UPongGameInstance::UPongGameInstance(const FObjectInitializer & ObjectInitializer)
{
    UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));

    ConstructorHelpers::FClassFinder<UMenuBase> MenuBPClass(TEXT("/Game/Menu/WBP_MainMenu"));
    if (!ensure(MenuBPClass.Class != nullptr)) return;
    MenuClass = MenuBPClass.Class;

      
    ConstructorHelpers::FClassFinder<UMenuBase> InGameMenuBPClass(TEXT("/Game/Menu/WBP_InGameMenu"));
    if (!ensure(InGameMenuBPClass.Class != nullptr)) return;
    InGameMenuClass = InGameMenuBPClass.Class;

}

void UPongGameInstance::Init()
{
    UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
    UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}

void UPongGameInstance::Host()
{
    UWorld* World = GetWorld();

    if (!ensure(World != nullptr)) return;

    World->ServerTravel("/Game/Maps/PongLevel?listen");

}

void UPongGameInstance::Join(const FString& Adress)
{
    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (!ensure(PlayerController != nullptr)) return;

    PlayerController->ClientTravel(Adress, ETravelType::TRAVEL_Absolute);
}

void UPongGameInstance::LoadMenu()
{
    if (!ensure(MenuClass != nullptr)) return;

    Menu = CreateWidget<UMainMenu>(this, MenuClass);

    if (!ensure(Menu != nullptr)) return;
    Menu->Setup();

    Menu->SetMenuInterface(this);
}

void UPongGameInstance::LoadInGameMenu()
{
    if (!ensure(InGameMenuClass != nullptr)) return;

    InGameMenu = CreateWidget<UInGameMenu>(this, InGameMenuClass);

    if (!ensure(InGameMenu != nullptr)) return;
    InGameMenu->Setup();

    InGameMenu->SetMenuInterface(this);
}

void UPongGameInstance::GoToMainMenu()
{
    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (!ensure(PlayerController != nullptr)) return;

    PlayerController->ClientTravel("/Game/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
}

void UPongGameInstance::QuitGame()
{
    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (!ensure(PlayerController != nullptr)) return;

    PlayerController->ConsoleCommand("quit");
}

