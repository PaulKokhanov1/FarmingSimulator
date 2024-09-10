// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"


// Unused at the moment
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FFloatStatUpdated,
	float, OldValue,
	float, NewValue,
	float, MaxValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDroppedFishingLocation, FVector, CastingLocation);



//Forward Declarations
class UCameraComponent;
class USpringArmComponent;
class UUserWidget;
class UTextBlock;
class UFishCaughtWidget;
class AFishingSphere;
class AFishingBuoy;
class UAnimSequence;

UCLASS()
class FARMING_SIM_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()


	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera = nullptr;


	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArm = nullptr;
	
public:
	// Sets default values for this character's properties
	AMainPlayer();

	FDroppedFishingLocation CastingRelease;

	void HideFisingWidget();
	void RemoveBuoy();

	FVector CastDirection;
	FVector CastLocation;
	float CastDistance;
	float DistanceIncreaseRate = 100.0f;	//how fast the line is increasing from the character

	bool bIsWaitingForFish;

	UPROPERTY(EditAnywhere, Category = "Player|Fishing")
	float MaxCastDistance = 700.0f;		//the furthest the line can go

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimSequence> MoveAnimation;


	UPROPERTY(EditAnywhere)
	TSubclassOf<AFishingSphere> SphereActor;

	TObjectPtr<AFishingSphere> FishingSphere;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFishingBuoy> BuoyActor;

	TObjectPtr<AFishingBuoy> BuoyObject;

	//TEMPORARY FUNCTION JUST FOR TESTING
	UFUNCTION(BlueprintCallable, Category = "Player|Fishing", meta = (AllowPrivateAccess = "true"))
	void CatchFish();

	UFUNCTION(BlueprintCallable, Category = "Player|Fishing", meta = (AllowPrivateAccess = "true"))
	void CastFishingLine(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Player|Fishing", meta = (AllowPrivateAccess = "true"))
	bool ReleaseFishingLine();

	UFUNCTION(BlueprintCallable, Category = "Player|Fishing", meta = (AllowPrivateAccess = "true"))
	FVector GetFishingBuoyReleaseLocation();

	UFUNCTION(BlueprintCallable, Category = "Player|Fishing", meta = (AllowPrivateAccess = "true"))
	FVector GetCastingStartLocation();

	UFUNCTION(BlueprintCallable, Category = "Player|Fishing")
	void SetFishing(bool IsFishing);

	UFUNCTION(BlueprintCallable, Category = "Player|Fishing")
	void SetHasFished(bool IsFishing);

	UFUNCTION(BlueprintCallable, Category = "Player|Fishing")
	void ToggleFishing();

	#pragma region Stamina

		// Return the player's current stamina.
		UFUNCTION(BlueprintPure, Category = "Player|Fishing Stamina")
		float GetFishingStamina();

		// Return the cost of throwing the line.
		UFUNCTION(BlueprintPure, Category = "Player|Fishing Stamina")
		float GetFishingThrowingStaminaCost();

		// Return the player's current recuperation factor.
		UFUNCTION(BlueprintPure, Category = "Player|Fishing Stamina")
		float GetFishingStaminaRechargeRate();

		UFUNCTION(BlueprintCallable, Category = "Player|Fishing Stamina")
		void SetFishingStaminaRechargeRate(float NewFishingStaminaRechargeRate);

		// Triggered when the player's stamina is updated.
		UPROPERTY(BlueprintAssignable, Category = "Player|Fishing Stamina")
		FFloatStatUpdated OnFishingStaminaChanged;

	#pragma endregion

		// Called every frame
		virtual void Tick(float DeltaTime) override;

		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WidgetClass;



	// is the character currently set to Fish?
	bool bIsFishing = false;

	// did the character fish since the last update?
	bool bHasFished = false;


	//Fishing Stamina
	static constexpr float maxFishingStamina = 100.0f;
	static constexpr float fishingThrowStaminaCost = 25.0f;	//initial throw
	static constexpr float fishingStaminaCost = 1.0f;	//whilist fishing, mighth be a stupid feature but we'll see
	float currentFishingStamina = maxFishingStamina;
	float fishingRechargeRate = 1.0f;

	//Make sure the class is UFishCaughtWidget and not UUserWidget to be able to use the user-defined function of UFishCaughtWidget
	TObjectPtr<UFishCaughtWidget> wdgFishInfo;


	//Might not be best practice but using this to implement a delay in executing certain fucntions within the tick method since I can't adjust the tick interval due to the reliance of other aspects of the code
	float TimeSinceLastUpdate;





};
