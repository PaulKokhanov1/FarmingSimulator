// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "FarmingPlayerController.generated.h"

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	UInputAction* ActionMove = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	UInputAction* ActionLook = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	UInputAction* ActionFish = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Testing Input")
	UInputAction* ActionTest = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Fishing Input")
	UInputAction* ActionCatchFish = nullptr;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|UI")
	UInputAction* ActionCloseUI = nullptr;

	// The Input Mapping Context to use.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	UInputMappingContext* InputMappingContent = nullptr;


	// The Input Mapping Context to use while player is waiting for fish
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	UInputMappingContext* InputMappingContentFishing = nullptr;



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
	void HandleFish();
	void CastLine();
	void UnCastLine();
	void HandleTest();
	void CatchFish();
	void CloseUI();

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	
};
