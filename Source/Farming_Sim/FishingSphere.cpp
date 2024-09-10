// Fill out your copyright notice in the Description page of Project Settings.


#include "Farming_Sim/FishingSphere.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Farming_Sim/FishingLocation.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Materials/Material.h"

// Sets default values
AFishingSphere::AFishingSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	//Creating Projectile Component
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere Mesh"));
	RootComponent = SphereMesh;

	SphereComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Sphere Component"));
	SphereMesh->SetMobility(EComponentMobility::Movable);
}

// Called when the game starts or when spawned
void AFishingSphere::BeginPlay()
{
	Super::BeginPlay();

	SphereMesh->OnComponentBeginOverlap.AddDynamic(this, &AFishingSphere::OnOverlapStart);	//Looks at if AFishingSphere is overlapping and call OnoverlapStart
	SphereMesh->OnComponentEndOverlap.AddDynamic(this, &AFishingSphere::OnOverlapEnd);
	
}

void AFishingSphere::OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapping is starting"));
	TObjectPtr<AFishingLocation> fishingArea = Cast<AFishingLocation>(OtherActor);	// if otherActor invovled in overlap then is stored in this pointer "FishingArea"
	if (fishingArea != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("FishingArea is detected"));
		ChangeMaterialColor(DynamicMaterialGreen);
		overlappingFishingLocation = true;
	}
}

void AFishingSphere::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapping is ending"));
	ChangeMaterialColor(DynamicMaterialRed);
	overlappingFishingLocation = false;



}


bool AFishingSphere::GetoverlappingFishingLocation()
{
	return overlappingFishingLocation;
}

void AFishingSphere::ChangeMaterialColor(UMaterial* Material)
{
	if (Material) {
		SphereMesh->SetMaterial(0, Material);

	}
}

