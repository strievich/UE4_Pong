// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuBase.h"
#include "MenuInterface.h"

void UMenuBase::Setup()
{
    AddToViewport();

    UWorld* World = GetWorld();

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if (!ensure(PlayerController != nullptr)) return;

    FInputModeUIOnly InputMode;
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    InputMode.SetWidgetToFocus(TakeWidget());
    PlayerController->SetInputMode(InputMode);
    PlayerController->bShowMouseCursor = true;
}

void UMenuBase::Teardown()
{
    RemoveFromViewport();
    UWorld* World = GetWorld();

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if (!ensure(PlayerController != nullptr)) return;

    FInputModeGameOnly InputMode;
    PlayerController->SetInputMode(InputMode);
    PlayerController->bShowMouseCursor = false;
}

void UMenuBase::SetMenuInterface(IMenuInterface* InMenuInterface)
{
    this->MenuInterface = InMenuInterface;
}

void UMenuBase::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
    //Teardown();
}
