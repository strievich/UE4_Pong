// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MenuBase.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API UMenuBase : public UUserWidget
{
	GENERATED_BODY()

public:
    void Setup();

    void Teardown();

    void SetMenuInterface(class IMenuInterface* InMenuInterface);
    virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld);

protected:

    class IMenuInterface* MenuInterface;
};
