// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollector.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "Kismet/GameplayStatics.h"


ABatteryCollectorGameMode::ABatteryCollectorGameMode()
{
    // set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
    if (PlayerPawnBPClass.Class != nullptr)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
    DecayRate = 0.01f;
}

void ABatteryCollectorGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    ABatteryCollectorCharacter* MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (MyCharacter)
    {
        if (MyCharacter->GetCurrentPower() > PowerToWin)
        {
            SetCurrentState(EBatteryPlayState::EWon);
        }
        else if (MyCharacter->GetCurrentPower() > 0)
        {
            MyCharacter->UpdatePower(-DeltaTime * DecayRate * MyCharacter->GetInitialPower());
        }
        else if (MyCharacter->GetCurrentPower() < 0 )
        {
            SetCurrentState(EBatteryPlayState::EGameOver);
        }
        else
        {
            SetCurrentState(EBatteryPlayState::EUnknown);
        }
    }
}

void ABatteryCollectorGameMode::BeginPlay()
{
    Super::BeginPlay();
    SetCurrentState(EBatteryPlayState::EPlaying);

    //set the score to win
    ABatteryCollectorCharacter* MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (MyCharacter && MyCharacter->GetCurrentPower() > 0)
    {
        PowerToWin = MyCharacter->GetInitialPower() * 1.25f;
    }

    if (HUDWidgetClass != nullptr)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);


        if (CurrentWidget != nullptr)
            CurrentWidget->AddToViewport();
    }
}

float ABatteryCollectorGameMode::GetPowerToWin() const
{
    return PowerToWin;
}

EBatteryPlayState ABatteryCollectorGameMode::GetCurrentState() const
{
    return CurrentState;
}

void ABatteryCollectorGameMode::SetCurrentState(EBatteryPlayState NewState)
{
    CurrentState = NewState;
}
