// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "BatteryCollectorCharacter.generated.h"

UCLASS(config = Game)
class ABatteryCollectorCharacter : public ACharacter
{
    GENERATED_BODY()

        /** Camera boom positioning the camera behind the character */
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        class USpringArmComponent* CameraBoom;

    /** Follow camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        class UCameraComponent* FollowCamera;

    /** Collection Sphere */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        class USphereComponent* CollectionSphere;
public:
    ABatteryCollectorCharacter();

    /** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
        float BaseTurnRate;

    /** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
        float BaseLookUpRate;

    /** Accessor function for initial power */
    UFUNCTION(BlueprintPure, Category = "Power")
        float GetInitialPower() const;

    /** Accessor function for current power */
    UFUNCTION(BlueprintPure, Category = "Power")
        float GetCurrentPower() const;

    /**
     * @param PowerChange The amount to change CharacterPower by.
     */
    UFUNCTION(BlueprintCallable, Category = "Power")
        void UpdatePower(float PowerChange);

protected:

    /** Resets HMD orientation in VR. */
    void OnResetVR();

    /** Called for forwards/backward input */
    void MoveForward(float Value);

    /** Called for side to side input */
    void MoveRight(float Value);

    /**
     * Called via input to turn at a given rate.
     * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
     */
    void TurnAtRate(float Rate);

    /**
     * Called via input to turn look up/down at a given rate.
     * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
     */
    void LookUpAtRate(float Rate);

    /** Handler for when a touch input begins. */
    void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

    /** Handler for when a touch input stops. */
    void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
    // APawn interface
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    // End of APawn interface

    /** This function collects the pickups overlapping the CollectionSphere */
    UFUNCTION(BlueprintCallable, Category = "Pickups")
        void CollectPickups();

    /** Initial power level */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
        float InitialPower;

    /** Speed after power mod */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
        float SpeedFactor;

    /** Initial speed before power mod */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
        float BaseSpeed;

    UFUNCTION(BlueprintImplementableEvent)
        void PowerChangeEffect();

private:
    /** Current power level of the character */
    UPROPERTY(VisibleAnywhere, Category = "Power")
        float CharacterPower;

    TArray<class ASpawnVolume*> SpawnVolumeActors;

public:
    /** Returns CameraBoom subobject **/
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    /** Returns FollowCamera subobject **/
    FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
    /** Returns CollectionSphere subobject **/
    FORCEINLINE class USphereComponent* GetCollectionSphere() const { return CollectionSphere; }
};
