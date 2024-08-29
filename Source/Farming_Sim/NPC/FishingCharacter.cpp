#include "Farming_Sim/NPC/FishingCharacter.h"
#include "Algo/RandomShuffle.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AFishingCharacter::AFishingCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickInterval(5.0f);
	SetActorTickEnabled(true);

	//FOR NOW SET SEASON HERE BUT IDEALLY SET IT IN  EDITOR
	season = 1;
	
	n_100 = 100;
	top_50 = 50;
	alpha = 0.7;
	solLength = 6;
	p_m = 0.8; //probability of mutating a digit in solution sequence 

	//initialize season Optimal
	switch (season) {
	case 1:
		UE_LOG(LogTemp, Warning, TEXT("Season Optimal is: 123456"));
		seasonOptimal = 123456;
		break;

	case 2:
		UE_LOG(LogTemp, Warning, TEXT("Season Optimal is: 654321"));
		seasonOptimal = 654321;
		break;

	case 3:
		UE_LOG(LogTemp, Warning, TEXT("Season Optimal is: 456123"));
		seasonOptimal = 456123;
		break;

	case 4:
		UE_LOG(LogTemp, Warning, TEXT("Season Optimal is: 321654"));
		seasonOptimal = 321654;
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("Season is NOT one of the expected: {1,2,3,4}"));
		seasonOptimal = 0;
		break;
	}

	//------------------------------------------------------------------------------------------
	//Creating the Genetic Algorithm, initialization

	//Create initial random solutions, not super efficient implementation but will hopefully atleast work
	const int numInitialSolutions = 150;	//start w/ 150 solutions
	for (int i = 0; i < numInitialSolutions; i++) {

		//create initial solution
		TArray<int32> initialSolution;

		for (int j = 0; j < 6; j++) {
			int32 RandomValue = FMath::RandRange(0, 9);

			initialSolution.Add(RandomValue);
		}
		//initialize each fishStruct w/ initial sol, 0 rank and pass reference to the FishingCharacter class 
		FishGASolutions.Add(FFishStruct{ initialSolution, 0, this });
	}

	//Find fitness of each solution
	for (auto& s : FishGASolutions) { s.fitness(); }


}

//Used for calculation of real-valued GA crossover
int32 AFishingCharacter::simpleArthmeticCrossover(int32 A, int32 B)
{

	return FMath::RoundToInt32( (alpha * B) + ((1 - alpha)*A) );
}

// Called when the game starts or when spawned
void AFishingCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFishingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("TICK CALLED"));

	//------------------------------------------------------------------------------------------
	//Creating the Genetic Algorithm, one iteration per tick


	//Sort the solutions by rank
	FishGASolutions.Sort([](const auto& A, const auto& B) {
		return A.rank < B.rank;
		});

	//Print just to make sure, print top 10
	//for (int32 Index = 0; Index != 10; ++Index)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Rank: %f , Solution: %d %d %d %d %d %d"), FishGASolutions[Index].rank,
	//		FishGASolutions[Index].solution[0], 
	//		FishGASolutions[Index].solution[1], 
	//		FishGASolutions[Index].solution[2], 
	//		FishGASolutions[Index].solution[3], 
	//		FishGASolutions[Index].solution[4], 
	//		FishGASolutions[Index].solution[5]);
	//}

	//Parent Selection - Tournament Selection, choose 100 random, i.e k = 100, then select best 50, TODO: can make these #'s larger later
	//create shuffled solutions
	TArray<FFishStruct> shuffledFishGASolutions = FishGASolutions;
	Algo::RandomShuffle(shuffledFishGASolutions);

	//Create randomly selected Solutions
	TArray<FFishStruct> randomFishGASolutions = TArray<FFishStruct>(shuffledFishGASolutions.GetData(), n_100);

	//Then take best 50 solutions, first sort them
	randomFishGASolutions.Sort([](const auto& A, const auto& B) {
		return A.rank < B.rank;
		});

	//Then select first 50
	TArray<FFishStruct> parentFishGASolutions = TArray<FFishStruct>(randomFishGASolutions.GetData(), top_50);

	//RECOMBINATION - Simple Arithmetic Crossover
	TArray<FFishStruct> childFishGASolution;	//children, could just place these into the original TArray, but will optimize later
	int32 pairs = 50;	//define # of pairs, meaning we'd get 100 children, i.e 2 child per pair
	TArray<int32> childOneSolution;
	TArray<int32> childTwoSolution;
	for (int32 i = 0; i < pairs; i++) {

		//Choose two random parents, that are different
		int32 Index1 = FMath::RandRange(0, parentFishGASolutions.Num() - 1);
		int32 Index2;

		do
		{
			Index2 = FMath::RandRange(0, parentFishGASolutions.Num() - 1);
		} while (Index1 == Index2); // Ensure the indices are not the same 


		int32 k = FMath::RandRange(0, solLength-1);	//choose which bit to start the crossover from
		for (int32 j = 0; j < solLength; j++) {
			//Create child 1 solution
			if (j >= k) {
				childOneSolution.Add(simpleArthmeticCrossover(parentFishGASolutions[Index1].solution[j], parentFishGASolutions[Index2].solution[j]));
			}else {
				childOneSolution.Add(parentFishGASolutions[Index1].solution[j]);
			}

			//Create child 2 solution
			if (j >= k) {
				childTwoSolution.Add(simpleArthmeticCrossover(parentFishGASolutions[Index2].solution[j], parentFishGASolutions[Index1].solution[j]));
			}
			else {
				childTwoSolution.Add(parentFishGASolutions[Index2].solution[j]);
			}

		}
		//Add children to list
		childFishGASolution.Add(FFishStruct{ childOneSolution, 0, this });
		childFishGASolution.Add(FFishStruct{ childTwoSolution, 0, this });


		//Clear children TArrays
		childOneSolution.Empty();
		childTwoSolution.Empty();

	}

	//MUTATION - Uniform Mutation, i.e draw random digit between 0 & 9 w/ probability p_m

	//iterate through each child solution
	for (FFishStruct fish : childFishGASolution) {

		//iterate through each digit of solution, generating probability for each digit
		for (int32 j = 0; j < solLength; j++) {

			// Generate a random float between 0 and 1
			float RandomValue = FMath::FRand();

			//mutate only if the generated value is less than p_m
			if (RandomValue <= p_m) {
				fish.solution[j] = FMath::RandRange(0, 9);
			}
		}
	}

	//Then calculate fitness of each new child
	for (auto& s : childFishGASolution) { s.fitness(); }

	//Survivor Selection, Choose best amongst children and parents

	//clear FishGASolutions TArray and then add all parents and children
	FishGASolutions.Empty();
	for (auto& s : childFishGASolution) { FishGASolutions.Add(s); }
	for (auto& p : parentFishGASolutions) { FishGASolutions.Add(p); }

	//sort solutions by rank which is actually done on the next iteration/tick

	//maybe will need to add some convergence/termination conditions

}

// Called to bind functionality to input
void AFishingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void FFishStruct::fitness()
{
	//first concatenate the list into a number
	int num = 0;
	for (int32 Index = 0; Index != solution.Num(); ++Index)
	{
		num = num * 10 + solution[Index];
	}
	//calculate fitness
	//first ensure we have an instance of the Fishing Character Instance
	if (FishingCharacterInstance) {
		//Calculate how close the solution is to the Optimal Value
		//The closer we are to zero, the lower the rank
		rank = abs(FishingCharacterInstance->seasonOptimal - num);
		//UE_LOG(LogTemp, Warning, TEXT("The rank is: %f"), rank);

	}

}

