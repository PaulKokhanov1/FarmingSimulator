#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FishFeaturesEnum.h"
#include "FishingCharacter.generated.h"


USTRUCT(BlueprintType)
struct FFishStruct
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<int32> solution;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float rank;

	//To access the seasonOptimal variable
	AFishingCharacter* FishingCharacterInstance;


	void fitness();	// dont make this a UFUNCTION() because else UE5 won't allow it

};


UCLASS()
class FARMING_SIM_API AFishingCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFishingCharacter();

	//The season will determine which fish "solution" is optimal
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int season;

	//This will be initialized based on which season we are in
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int seasonOptimal;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int n_100;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int top_50;

	//Used for Crossover
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float alpha;

	//Used for Mutation
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float p_m;

	//The number of bits in the solutions
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 solLength;

	UPROPERTY(EditAnywhere)
	FFishStruct FishGA;

	UPROPERTY(EditAnywhere)
	TArray<FFishStruct> FishGASolutions;

	UFUNCTION(BlueprintCallable)
	int32 simpleArthmeticCrossover(int32 A, int32 B);

	//Mapping Enum values
	TMap<int32, FString> ColorMap = {
		{0, TEXT("Red")},
		{1, TEXT("Blue")},
		{2, TEXT("Green")},
		{3, TEXT("Yellow")},
		{4, TEXT("Black")},
		{5, TEXT("White")},
		{6, TEXT("Purple")},
		{7, TEXT("Orange")},
		{8, TEXT("Pink")},
		{9, TEXT("Brown")}
	};

	TMap<int32, FString> SizeMap = {
		{0, "0.5"},
		{1, "1.0"},
		{2, "1.5"},
		{3, "2.0"},
		{4, "2.5"},
		{5, "3.0"},
		{6, "3.5"},
		{7, "4.0"},
		{8, "4.5"},
		{9, "5.0"}
	};
	TMap<int32, FString> SpeedMap = {
		{0, "0.5"},
		{1, "1.0"},
		{2, "1.5"},
		{3, "2.0"},
		{4, "2.5"},
		{5, "3.0"},
		{6, "3.5"},
		{7, "4.0"},
		{8, "4.5"},
		{9, "5.0"}
	};

	TMap<int32, FString> TraitMap = {
		{0, TEXT("Aggressive")},
		{1, TEXT("Bottom Lurker")},
		{2, TEXT("Easily Spooked")},
		{3, TEXT("Hard Fighter")},
		{4, TEXT("Jumper")},
		{5, TEXT("Keen Senses")},
		{6, TEXT("Last Stand")},
		{7, TEXT("Night Owl")},
		{8, TEXT("Sun Lover")},
		{9, TEXT("Seaweed Enjoyer")}
	};
	TMap<int32, FString> TypeMap = {
		{0, TEXT("Barracuda")},
		{1, TEXT("Dogfish")},
		{2, TEXT("Gulper eel")},
		{3, TEXT("Haddock")},
		{4, TEXT("Killifish")},
		{5, TEXT("Limia")},
		{6, TEXT("Oregon chub")},
		{7, TEXT("Pigfish")},
		{8, TEXT("Redfish")},
		{9, TEXT("Shiner")}
	};

	TMap<int32, FString> IntelligenceMap = {
		{0, "0.5"},
		{1, "1.0"},
		{2, "1.5"},
		{3, "2.0"},
		{4, "2.5"},
		{5, "3.0"},
		{6, "3.5"},
		{7, "4.0"},
		{8, "4.5"},
		{9, "5.0"}
	};


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
