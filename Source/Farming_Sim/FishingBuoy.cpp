// Fill out your copyright notice in the Description page of Project Settings.


#include "Farming_Sim/FishingBuoy.h"

// Sets default values
AFishingBuoy::AFishingBuoy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFishingBuoy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFishingBuoy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

