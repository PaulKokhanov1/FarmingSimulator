// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FishingLocation.generated.h"

class UBoxComponent;

UCLASS()
class FARMING_SIM_API AFishingLocation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFishingLocation();

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess="true"))
	TObjectPtr<UBoxComponent> FishingAreaCollisionBox;

};
