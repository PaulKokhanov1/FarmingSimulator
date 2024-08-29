// Fill out your copyright notice in the Description page of Project Settings.

#include "Farming_Sim/NPC/FishCaughtWidget.h"
#include "Components/TextBlock.h"
#include "Farming_Sim/MainPlayer.h"
#include "Farming_Sim/NPC/FishingCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"



void UFishCaughtWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UE_LOG(LogTemp, Warning, TEXT("NativeOnInitialized()"));

}

void UFishCaughtWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (!FishAlgorithm.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("FishAlgorithm NOT initialized"));

    }
}

void UFishCaughtWidget::UpdateText()
{
	if (!FishColor || !FishSize || !FishSpeed || !FishTrait || !FishType || !FishIntelligence) return;

	int32 RandomValue = FMath::RandRange(0, 9);	//Just getting random value from top 10 solutions 

    //FString FormattedString = FString::Printf(TEXT("Rank: %f , Solution: %d %d %d %d %d %d"),
    //    FishAlgorithm->FishGASolutions[RandomValue].rank,
    //    FishAlgorithm->FishGASolutions[RandomValue].solution[0],
    //    FishAlgorithm->FishGASolutions[RandomValue].solution[1],
    //    FishAlgorithm->FishGASolutions[RandomValue].solution[2],
    //    FishAlgorithm->FishGASolutions[RandomValue].solution[3],
    //    FishAlgorithm->FishGASolutions[RandomValue].solution[4],
    //    FishAlgorithm->FishGASolutions[RandomValue].solution[5]);

    FString FishColorString = FishAlgorithm->ColorMap[FishAlgorithm->FishGASolutions[RandomValue].solution[0]];
    FString FishSizeString = FishAlgorithm->SizeMap[FishAlgorithm->FishGASolutions[RandomValue].solution[1]];
    FString FishSpeedString = FishAlgorithm->SpeedMap[FishAlgorithm->FishGASolutions[RandomValue].solution[2]];
    FString FishTraitString = FishAlgorithm->TraitMap[FishAlgorithm->FishGASolutions[RandomValue].solution[3]];
    FString FishTypeString = FishAlgorithm->TypeMap[FishAlgorithm->FishGASolutions[RandomValue].solution[4]];
    FString FishIntelligenceString = FishAlgorithm->IntelligenceMap[FishAlgorithm->FishGASolutions[RandomValue].solution[5]];

    FishColor->SetText(FText::FromString(FishColorString));
    FishSize->SetText(FText::FromString(FishSizeString));
    FishSpeed->SetText(FText::FromString(FishSpeedString));
    FishTrait->SetText(FText::FromString(FishTraitString));
    FishType->SetText(FText::FromString(FishTypeString));
    FishIntelligence->SetText(FText::FromString(FishIntelligenceString));

}
