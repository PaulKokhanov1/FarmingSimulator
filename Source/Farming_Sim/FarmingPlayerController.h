// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "FarmingPlayerController.generated.h"

//Forward Declarations
class AMainPlayer;
class UEnhancedInputComponent;
class UEnhancedInputLocalPlayerSubsystem;
class UInputMappingContext;
class UCameraComponent;


/**
 * 
 */
UCLASS(Abstract)
class FARMING_SIM_API AFarmingPlayerController : public APlayerController
{


public:

	//INPUT ACTIONS

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputAction> ActionMove = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputAction> ActionLook = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputAction> ActionFish = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Fishing Input")
	TObjectPtr<UInputAction> ActionCatchFish = nullptr;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|UI")
	TObjectPtr<UInputAction> ActionCloseUI = nullptr;

	// Default Input Mapping Context.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputMappingContext> InputMappingContent = nullptr;


	// The Input Mapping Context to use while player is waiting for fish
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputMappingContext> InputMappingContentFishing = nullptr;



	UFUNCTION()
	void SetInputDefault(const bool Enabled = true) const;

	UFUNCTION()
	void SetInputFishing(const bool Enabled = true) const;

private: 
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	UPROPERTY()
	AMainPlayer* PlayerCharacter = nullptr;

	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem;



	GENERATED_BODY()

protected:

	void HandleLook(const FInputActionValue& InputActionValue);
	void HandleMove(const FInputActionValue& InputActionValue);
	void CastLine();
	void UnCastLine();
	void CatchFish();
	void CloseUI();

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	
};
