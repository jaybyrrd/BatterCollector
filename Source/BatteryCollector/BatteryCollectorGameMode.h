// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "BatteryCollectorGameMode.generated.h"

//enum to store the game state
UENUM(BlueprintType)
enum class EBatteryPlayState : uint8
{
    EPlaying,
    EGameOver,
    EWon,
    EUnknown
};

UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameMode
{
    GENERATED_BODY()
public:
    ABatteryCollectorGameMode();
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintPure, Category = "Power")
        float GetPowerToWin() const;

    UFUNCTION(Blueprintpure, Category = "Power")
        EBatteryPlayState GetCurrentState() const;

    /** Sets a new playing state */
    void SetCurrentState(EBatteryPlayState NewState);

    virtual void BeginPlay() override;

protected:
    /** This rate at which the character loses power */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power")
        float DecayRate;

    /** Power needed to win the game */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
        float PowerToWin;

    /** The widget class to use for our hud */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
        TSubclassOf<class UUserWidget> HUDWidgetClass;

    /** The instance of the hud */
    UPROPERTY()
        class UUserWidget* CurrentWidget;

private:
    /** Keeps track of the current playing state */
    EBatteryPlayState CurrentState;
    TArray<class ASpawnVolume*> SpawnVolumeActors;

    /** Handles any function calls that rely upon changing the playing state of your game. */
    void HandleCurrentState();
};