
#include "Farming_Sim/MainPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Farming_Sim/NPC/FishCaughtWidget.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Farming_Sim/FishingSphere.h"
#include "Farming_Sim/FishingBuoy.h"
#include "Animation/AnimSequence.h"




// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(true);
	TimeSinceLastUpdate = 0.0f;
	CastDistance = 0.0f;

	//Setting Up Camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);


	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

}

//Called once player releases "SpaceBar"
void AMainPlayer::CatchFish()
{
	wdgFishInfo->SetVisibility(ESlateVisibility::Visible);

	wdgFishInfo->UpdateText();
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	SetFishing(false);
	bIsWaitingForFish = false;


}

FVector AMainPlayer::GetCastingStartLocation()
{
	return GetActorLocation() + (GetActorForwardVector() * 150) + FVector(0, 0, 50);
}



void AMainPlayer::HideFisingWidget()
{
	wdgFishInfo->SetVisibility(ESlateVisibility::Hidden);
}

void AMainPlayer::RemoveBuoy()
{
	BuoyObject->Destroy();
}

FVector AMainPlayer::GetFishingBuoyReleaseLocation()
{
	FVector ReleaseLocation;
	ReleaseLocation = FVector(CastLocation.X, CastLocation.Y, 0);
	return ReleaseLocation;
}


// Used to Move Sphere Actor in direction of the cast
void AMainPlayer::CastFishingLine(float DeltaTime)
{
	if (FishingSphere) {
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		CastDistance += DistanceIncreaseRate * DeltaTime;
		CastDistance = FMath::Clamp(CastDistance, 0.0f, MaxCastDistance);

		CastDirection = GetActorForwardVector();  // Assuming the cast is forward from the character

		CastLocation = GetCastingStartLocation() + CastDirection * CastDistance;

		FishingSphere->SetActorLocation(CastLocation);

		// Draw the debug object (e.g., a line) from the start location to the current cast location
		//DrawDebugSphere(GetWorld(), CastLocation, 20.0f, 12, FColor::Blue, false, -1, 0, 2.0f);
	}
	else {
		FishingSphere = GetWorld()->SpawnActor<AFishingSphere>(SphereActor, GetCastingStartLocation(), GetActorRotation());
	}


}

bool AMainPlayer::ReleaseFishingLine()
{
	CastDistance = 0.0f;
	if (FishingSphere->GetoverlappingFishingLocation()) {
		CastingRelease.Broadcast(CastLocation);	// broadcast the delegate, passing in the current location of the fishing sphere
		UE_LOG(LogTemp, Warning, TEXT("In Acceptable fishing Lcoation"));
		BuoyObject = GetWorld()->SpawnActor<AFishingBuoy>(BuoyActor, GetFishingBuoyReleaseLocation(), GetActorRotation());
		bIsWaitingForFish = true;
		return true;
	}
	else {
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		bIsWaitingForFish = false;
		return false;

	}
}

void AMainPlayer::SetFishing(bool IsFishing)
{
	// Set the value
	bIsFishing = IsFishing;

}

//Setting the initial toss of the line
void AMainPlayer::SetHasFished(bool HasFished)
{
	// Set the value
	bHasFished = HasFished;

}

void AMainPlayer::ToggleFishing()
{
	SetFishing(!bIsFishing);
}

float AMainPlayer::GetFishingStamina()
{
	return currentFishingStamina;
}

float AMainPlayer::GetFishingThrowingStaminaCost()
{
	return fishingThrowStaminaCost;
}

float AMainPlayer::GetFishingStaminaRechargeRate()
{
	return fishingRechargeRate;
}

void AMainPlayer::SetFishingStaminaRechargeRate(float NewFishingStaminaRechargeRate)
{
	//Check to see if its above zero because -ve wouldn't make much sense
	if (NewFishingStaminaRechargeRate > 0) {
		fishingRechargeRate = NewFishingStaminaRechargeRate;
	}
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	wdgFishInfo = CreateWidget<UFishCaughtWidget>(GetGameInstance(), WidgetClass);

	wdgFishInfo->AddToViewport();
	wdgFishInfo->SetVisibility(ESlateVisibility::Collapsed);

	
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeSinceLastUpdate += DeltaTime;

	//Stamina is constantly regenerating hence I probably need to keep this in the tick method

	if (bIsFishing) {
		CastFishingLine(DeltaTime);
	}

#pragma region Update Fishing Stamina
	if (TimeSinceLastUpdate >= 0.5f)
	{
		// How has fishing affected the stamina
		// First we set the recharge rate to a default value 
		// then alter it depending on whether the player threw the rod or is currently fishing

		float actualFishingStaminaRechargeRate = fishingRechargeRate;

		if (bHasFished) actualFishingStaminaRechargeRate = -fishingThrowStaminaCost;
		// If the sprinted then they get a deduction
		else if (bIsFishing || bIsWaitingForFish) actualFishingStaminaRechargeRate = -fishingStaminaCost;

		// Keep track of the value before it is changed.
		const float previousFishingStamina = currentFishingStamina;

		// Update the current value, capping it to the min and max allowable
		currentFishingStamina = FMath::Clamp(currentFishingStamina + actualFishingStaminaRechargeRate, 0.f, maxFishingStamina);

		// If the value has actually changed, we need to notify any listeners
		if (currentFishingStamina != previousFishingStamina)
		{
			OnFishingStaminaChanged.Broadcast(previousFishingStamina, currentFishingStamina, maxFishingStamina);
		}

		// Reset the flags to not constantly remove throwing stamina after initial toss
		bHasFished = false;

		//If player is still fishing while stamina runs out and reanable ability to walk
		if (currentFishingStamina <= 0) {
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
			SetFishing(false);
		}
#pragma endregion


		// display debug info
		GEngine->AddOnScreenDebugMessage(-1, 0.49f, FColor::Orange,
			*(FString::Printf(
				TEXT("Fishing - IsFishing:%d"), bIsFishing)));

		GEngine->AddOnScreenDebugMessage(-1, 0.49f, FColor::Silver,
			*(FString::Printf(
				TEXT("Fishing Stamina - Current:%f | Maximum:%f"), currentFishingStamina, maxFishingStamina)));

		TimeSinceLastUpdate -= 0.5f;
	}

}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

