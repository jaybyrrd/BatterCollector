// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYCOLLECTOR_API ABatteryPickup : public APickup
{
	GENERATED_BODY()
	
public: 
	// Sets default values for this actor's properties
	ABatteryPickup();
	
	//Overrides from the base class.
	void WasCollected_Implementation() override;
};
