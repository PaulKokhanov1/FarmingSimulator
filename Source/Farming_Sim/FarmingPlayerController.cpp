// Fill out your copyright notice in the Description page of Project Settings.


#include "Farming_Sim/FarmingPlayerController.h"
#include "Farming_Sim/MainPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void AFarmingPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	//Store reference to player's Pawn
	PlayerCharacter = Cast<AMainPlayer>(aPawn);
	checkf(PlayerCharacter, TEXT("AFarmingPlayerController derived classes should only posess AMainPlayer derived pawns"));

	//Store reference to EnhancedInputComponent
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("Unable to get reference to EnhancedInputComponent"));


	// Get local Player Subsystem
	InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystem, TEXT("Unable to get reference to the EnhancedInputLocalPlayerSubsystem. "));

	//Wipe Existing Mappings, and add our mapping
	checkf(InputMappingContent, TEXT("InputMappingContent not found"));
	InputSubsystem->ClearAllMappings();
	SetInputDefault();

	//Then we need to bind the input actions
	if (ActionMove) {
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this,
			&AFarmingPlayerController::HandleMove);
	}

	if (ActionLook) {
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this,
			&AFarmingPlayerController::HandleLook);
	}

	if (ActionFish) {
		//We use ETriggerEvent::Started and Canceled instead of IE_Pressed & IE_Released because I think the new UE5 enhanced input doesnt use those triggers in code anymore and so these trigger events do the same thing
		EnhancedInputComponent->BindAction(ActionFish, ETriggerEvent::Started, this,
			&AFarmingPlayerController::CastLine);
		EnhancedInputComponent->BindAction(ActionFish, ETriggerEvent::Canceled, this,
			&AFarmingPlayerController::UnCastLine);
	}

	if (ActionTest) {
		EnhancedInputComponent->BindAction(ActionTest, ETriggerEvent::Triggered, this,
			&AFarmingPlayerController::HandleTest);
	}

	if (ActionCatchFish) {
		EnhancedInputComponent->BindAction(ActionCatchFish, ETriggerEvent::Triggered, this,
			&AFarmingPlayerController::CatchFish);
	}

	if (ActionCloseUI) {
		EnhancedInputComponent->BindAction(ActionCloseUI, ETriggerEvent::Triggered, this,
			&AFarmingPlayerController::CloseUI);
	}
}

void AFarmingPlayerController::OnUnPossess()
{
	//Unbind
	EnhancedInputComponent->ClearActionBindings();

	//Call Parent
	Super::OnUnPossess();
}



void AFarmingPlayerController::SetInputDefault(const bool Enabled) const
{
	if (Enabled && InputSubsystem) {
		InputSubsystem->AddMappingContext(InputMappingContent, 0);
	}
	else if (!Enabled && InputSubsystem) {
		InputSubsystem->RemoveMappingContext(InputMappingContent);
	}
}

void AFarmingPlayerController::SetInputFishing(const bool Enabled) const
{
	if (Enabled && InputSubsystem) {
		InputSubsystem->AddMappingContext(InputMappingContentFishing, 1);
	}
	else if (!Enabled && InputSubsystem) {
		InputSubsystem->RemoveMappingContext(InputMappingContentFishing);
	}
}

void AFarmingPlayerController::HandleLook(const FInputActionValue& InputActionValue)
{
	//Get the input
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	//add the appropriate looking to the controller
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);

}

void AFarmingPlayerController::HandleMove(const FInputActionValue& InputActionValue)
{

	//First take in the action that is performed
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	//Then we need to apply this movement to the character/player
	if (PlayerCharacter) {
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementVector.Y);
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), MovementVector.X);
	}
}

void AFarmingPlayerController::HandleFish()
{

	if (PlayerCharacter) {
		PlayerCharacter->Fish(); 
		//GEngine->AddOnScreenDebugMessage(-1, 0.49f, FColor::Silver,*(FString::Printf(TEXT("Player Has fished"))));
	}
}

void AFarmingPlayerController::CastLine()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.49f, FColor::Silver, *(FString::Printf(TEXT("Player Has Cast the line"))));
	if (PlayerCharacter) {
		PlayerCharacter->HideFisingWidget();
		//To make sure the player only can throw when they have enough stamina
		if (PlayerCharacter->GetFishingStamina() > PlayerCharacter->GetFishingThrowingStaminaCost()) {

			PlayerCharacter->SetFishing(true);
			PlayerCharacter->SetHasFished(true);

		}
	}
}

void AFarmingPlayerController::UnCastLine()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.49f, FColor::Silver, *(FString::Printf(TEXT("Player Has Realed in the line"))));
	if (PlayerCharacter) {
		PlayerCharacter->SetFishing(false);

		if (PlayerCharacter->ReleaseFishingLine()) {
			//will switch the input mapping context
			SetInputDefault(false);
			SetInputFishing();	//HAVE TO REMEMBER TO RESTORE DEFAULT MAPPING AFTER CATHCING FISH
		}

	}
}


void AFarmingPlayerController::HandleTest()
{

	if (PlayerCharacter) {
		PlayerCharacter->CatchFish();
	}
}

void AFarmingPlayerController::CatchFish()
{
	if (PlayerCharacter) {
		PlayerCharacter->CatchFish();
		PlayerCharacter->RemoveBuoy();
	}
	SetInputFishing(false);
	SetInputDefault();

}

void AFarmingPlayerController::CloseUI()
{
	if (PlayerCharacter) {
		PlayerCharacter->HideFisingWidget();
	}
}

