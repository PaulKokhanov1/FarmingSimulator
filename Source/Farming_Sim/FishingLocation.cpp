// Fill out your copyright notice in the Description page of Project Settings.


#include "Farming_Sim/FishingLocation.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AFishingLocation::AFishingLocation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FishingAreaCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FishingAreCollisionBox"));

}


// Called when the game starts or when spawned
void AFishingLocation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFishingLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

