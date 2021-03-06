// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API ASpawnVolume : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ASpawnVolume();

    // Returns the WhereToSpawn subobject
    FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

    // Returns a random point in the volume
    UFUNCTION(BlueprintPure, Category = "Spawning")
        FVector GetRandomPointInVolume();

    UFUNCTION(BlueprintCallable, Category = "Spawning")
        void SetSpawningActive(bool bShouldSpawn);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // The pickup to spawn
    UPROPERTY(EditAnywhere, Category = "Spawning")
        TSubclassOf<class APickup> WhatToSpawn;

    FTimerHandle SpawnTimer;

    //Minimum spawn delay
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
        float SpawnDelayMinimum;

    //Maximum spawn delay
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
        float SpawnDelayMaximum;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    //Box Component to Specify where pickups should be spawned.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
        class UBoxComponent* WhereToSpawn;

    //Handles spawning new pickup
    void SpawnPickup();

    //The currentspawn delay
    float SpawnDelay;
};
