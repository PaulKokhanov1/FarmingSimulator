// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FishingSphere.generated.h"


//Forward Declarations
class UProjectileMovementComponent;
class UMaterial;


UCLASS()
class FARMING_SIM_API AFishingSphere : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFishingSphere();

	bool GetoverlappingFishingLocation();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> SphereMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UProjectileMovementComponent> SphereComponent;

	void ChangeMaterialColor(UMaterial* Material);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterial> DynamicMaterialGreen;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterial> DynamicMaterialRed;

	bool overlappingFishingLocation;


};
