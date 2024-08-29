#pragma once

#include "CoreMinimal.h"
#include "FishFeaturesEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EFishFeaturesEnum : uint8
{
    Color UMETA(DisplayName = "Color"),
    Size UMETA(DisplayName = "Size"),
    Speed UMETA(DisplayName = "Speed"),
    Trait UMETA(DisplayName = "Trait"),
    Type UMETA(DisplayName = "Type"),
    Intelligence UMETA(DisplayName = "Intelligence")
};

