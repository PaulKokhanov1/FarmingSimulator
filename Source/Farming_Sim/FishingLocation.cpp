// Fill out your copyright notice in the Description page of Project Settings.


#include "Farming_Sim/FishingLocation.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

// Used to create the Collision Box that is used to determine if the player is casting in an allowed fishing location
AFishingLocation::AFishingLocation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FishingAreaCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FishingAreCollisionBox"));

}


