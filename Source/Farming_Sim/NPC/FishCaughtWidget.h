// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FishCaughtWidget.generated.h"

//Forward Declarations
class UTextBlock;
class AFishingCharacter;

UCLASS()
class FARMING_SIM_API UFishCaughtWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> FishColor;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> FishSize;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> FishSpeed;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> FishTrait;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> FishType;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> FishIntelligence;


public:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateText();


	//Needs to be a SoftObjectPtr because we can't set a hard reference to a level actor from a Widget that doesn't exist in the level yet, also I set this in the editor
	UPROPERTY(EditAnywhere, Category = "Algorithm")
	TSoftObjectPtr<AFishingCharacter> FishAlgorithm;


};
