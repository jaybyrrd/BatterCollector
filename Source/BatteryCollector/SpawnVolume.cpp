// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "Kismet/KismetMathLibrary.h"
#include "SpawnVolume.h"
#include "Pickup.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    //Create the Box Component to represent the spawn volume
    WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
    RootComponent = WhereToSpawn;

    //Set the spawn delay range
    SpawnDelayMinimum = 1.0f;
    SpawnDelayMaximum = 4.5f;
}

FVector ASpawnVolume::GetRandomPointInVolume()
{
    FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
    FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;
    return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void ASpawnVolume::SetSpawningActive(bool bShouldSpawn)
{
    if (bShouldSpawn)
    {
        //Set the timer on spawn pickup
        SpawnDelay = FMath::FRandRange(SpawnDelayMinimum, SpawnDelayMaximum);
        GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
    }
    else
    {
        GetWorldTimerManager().ClearTimer(SpawnTimer);
    }
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASpawnVolume::SpawnPickup()
{
    if (WhatToSpawn != NULL)
    {
        UWorld* const World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = Instigator;

            //Get a random location to spawn in:
            FVector SpawnLocation = GetRandomPointInVolume();

            //Get a random rotation for the spawned item
            FRotator SpawnRotation;
            SpawnRotation.Yaw = FMath::FRand() * 360.0f;
            SpawnRotation.Pitch = FMath::FRand() * 360.0f;
            SpawnRotation.Roll = FMath::FRand() * 360.0f;

            // Spawn the pickup
            APickup* const SpawnedPickup = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation);

            SpawnDelay = FMath::FRandRange(SpawnDelayMinimum, SpawnDelayMaximum);
            GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
        }
    }
}