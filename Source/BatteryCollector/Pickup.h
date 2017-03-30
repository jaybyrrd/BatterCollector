// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API APickup : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    APickup();

    // Returns whether or not the pickup is active.
    UFUNCTION(BlueprintPure, Category = "Pickup")
        bool IsActive() const;

    //Allows other classes to safely change the pickup active status
    UFUNCTION(BlueprintCallable, Category = "Pickup")
        void SetActive(bool NewPickupState);

    //Function to call when a pickup is collected
    UFUNCTION(BlueprintNativeEvent)
        void WasCollected();
    virtual void WasCollected_Implementation();

    // Called every frame
    virtual void Tick(float DeltaTime);

    /** Return the mesh for the pickup */
    FORCEINLINE class UStaticMeshComponent* GetMesh() const { return PickupMesh; }

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    /** True when the pickup can be used, and false when pickup is deactivated */
    bool bIsActive;

private:
    /** Static mesh to represent the pickup in the level */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
        class UStaticMeshComponent* PickupMesh;
};
