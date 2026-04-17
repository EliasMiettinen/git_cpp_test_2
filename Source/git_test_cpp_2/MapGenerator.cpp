// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGenerator.h"

#include <cmath>

#include "Kismet/GameplayStatics.h"


// Sets default values
AMapGenerator::AMapGenerator()
{
 	// Disable ticking
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMapGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	// Find the Map class
	Map = Cast<AMap>(UGameplayStatics::GetActorOfClass(GetWorld(), AMap::StaticClass()));
	
	// Get the tile set
	if (Map)
	{
		TileSet = Map->TileSet;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MapGenerator: Failed to find AMap actor"));
		return;
	}
	
	// Update the map size to the Map class
	Map->SetMapSize(MapSizeX, MapSizeY);
	
	// Initialize the water spawner location
	RowPos = GetActorLocation();
	TilePos = RowPos;
	
	// Initialize ground generation
	TotalContinents = FMath::Clamp(static_cast<int32>(std::ceil(GroundPercentage / 10.0f)), 2, 50);
	ContinentsGenerated = 0;
	
	// Initialize forest generation
	TotalForests = FMath::Clamp(static_cast<int32>(std::ceil(ForestPercentage / 10.0f)) + ((MapSizeX / 2) / 6),2, 50) + 3;
	ForestsGenerated = 0;
	
	// Initialize swamp generation
	TotalSwamps = FMath::Clamp(static_cast<int32>(std::ceil(SwampPercentage / 7.0f)), 2, 50) + 1;
	SwampsGenerated = 0;
	
	// Initialize mountain generation
	TotalMountainRanges = FMath::Clamp(static_cast<int32>(std::ceil(MountainPercentage / 6.0f)) + ((MapSizeX / 2) / 6), 1, 50) + 1;
	MountainRangesGenerated = 0;
	
	// Initialize hill generation
	TotalHills = FMath::Clamp(static_cast<int32>(std::ceil(HillPercentage / 7.0f)) + ((MapSizeX / 2) / 5), 2, 50) + 2;
	HillsGenerated = 0;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Total Continents: " + FString::FromInt(TotalContinents));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Total Forests: " + FString::FromInt(TotalForests));
	
	bIsGenerating = false;
	CurrentStage = 0;
}

// Called every frame
void AMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Check if generator is on
	if (bIsGenerating)
	{		
		// Count the time to next step
		TimeToNextStep -= GetWorld()->GetDeltaSeconds();
		
		// Take the next step & reset the timer
		if (TimeToNextStep <= 0)
		{
			TimeToNextStep = DelayBetweenSteps;
			NextStep();
		}
	}
}

void AMapGenerator::GenerateMap()
{
	// Validate required components
	if (!GetWorld() || !TileSet || !TileClass)
		return;
	
	// Start the generator
	bIsGenerating = true;
}

/**
 * @brief Advances map generation to the next stage.
 *
 * Executes the current generation stage and increments to the next.
 * Stages: 0-Water, 1-Continents, 2-Forests, 3-Swamps, 4-Mountains.
 * Stops when all the stages are complete.
 */
void AMapGenerator::NextStep()
{
	// Switch from the stage to the next
	switch (CurrentStage)
	{
		case 0:							// Generate Water
			GenerateWaterRow();
			break;
		case 1:							// Generate Continents
			GenerateContinent();
			break;
		case 2:							// Generate Forests
			GenerateForest();
			break;
		case 3:							// Generate Swamps
			GenerateSwamp();
			break;
		case 4:							// Generate Mountain Ranges
			GenerateMountainRange();
			break;
		case 5:
			GenerateHillFormation();
			break;
		default:
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Finished swamp generation");
			bIsGenerating = false;
			break;
	}
}

/**
 * @brief Generates a row of water tiles and prepares for the next stage of map generation.
 *
 * Calculates the starting position for a new row of water tiles based on the current row's position.
 * Iterates through the specified number of tiles (MapSizeX) in the row, spawning new tiles of the
 * TileClass type and adding them to the Map. Adjusts the position for each subsequent tile and prepares
 * for the next row once all tiles in the current row are generated. When all rows (based on MapSizeY)
 * are completed, transitions to the next generation stage.
 *
 * Increments the CurrentRow counter to track progress and updates the CurrentStage when all
 * water rows are fully generated.
 *
 * Displays a debug message once water generation is complete.
 */
void AMapGenerator::GenerateWaterRow()
{	
	RowPos = FVector(RowPos.X + 150, RowPos.Y, RowPos.Z);
	TilePos = FVector(RowPos.X, TilePos.Y + (CurrentRow % 2 == 0 ? 0 : 86.6f), RowPos.Z);

	// Loop all the tiles in the row
	for (int32 j = 1; j <= MapSizeX; j++)
	{
		// Spawn a new tile and add it to Map
		ATile* NewTile = GetWorld()->SpawnActor<ATile>(TileClass, TilePos, FRotator::ZeroRotator);
		Map->AddTile(NewTile);
			
		// Get ready for the next tile
		TilePos = FVector(TilePos.X, TilePos.Y + 173.199997f, TilePos.Z);
	}
		
	// Get ready for the next row
	TilePos = FVector(TilePos.X, GetActorLocation().Y, TilePos.Z);
	
	// Go to the next row
	CurrentRow++;
	
	// When all the rows are generated, move on to the next stage
	if (CurrentRow > MapSizeY)
	{
		CurrentStage++;
		CurrentRow = 1;
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Finished water generation");
	}
}

/**
 * @brief Generates a single continent by converting water tiles to plain tiles.
 *
 * Creates a continent based on GroundPercentage and TotalContinents settings.
 * Starting from a random tile, progressively converts water tiles to plain tiles,
 * randomly spreading to neighboring tiles until the target tile count is reached.
 *
 * Increments ContinentsGenerated counter. Once all continents are complete,
 * move on to the next stage
 */
void AMapGenerator::GenerateContinent()
{
	// Get the startgin tile
	int32 TileIndex = Map->GetRandomTileIndex();
	
	// Calculate total count of tiles for continent
	int32 TotalTiles = static_cast<int32>(std::round((Map->GetTileListLength() * (GroundPercentage / 100.0f)) / TotalContinents));
	int32 TilesGenerated = 0;
	
	int32 KillCounter = 0;

	// Generate all the tiles in one continent
	while (TilesGenerated < TotalTiles)
	{
		KillCounter++;
		if (KillCounter > 100000) { break; }
		
		ATile* Tile = Map->GetTileAtIndex(TileIndex);
		
		// Only change tile to plain if it is water
		if (Tile->IsTileType(ETileType::Water))
		{
			Tile->ChangeType(Map->TileSet->Plain);
			TilesGenerated++;
		}
		
		// Get all available neighbors
		TArray<int32> NeighboringTiles = Map->GetNeighboringTiles(TileIndex);
		
		// Get new tile index to continue generation
		TileIndex = NeighboringTiles[FMath::RandRange(0, NeighboringTiles.Num() - 1)];
		
		// Roll a random to see if neighbors should be changed to plain
		for (auto NeighboringTile : NeighboringTiles)
		{
			if (FMath::RandBool())
			{
				ATile* NeighboringTileObj = Map->GetTileAtIndex(NeighboringTile);
				// Change neighboring tile to plain if it is water
				if (NeighboringTileObj->IsTileType(ETileType::Water))
				{
					NeighboringTileObj->ChangeType(Map->TileSet->Plain);		
					TilesGenerated++;
				}
			}
		}
	}
	
	// Count one continent generated
	ContinentsGenerated++;
	
	// If all of the continents are generated, finish ground generation
	if (ContinentsGenerated >= TotalContinents)
	{
		CurrentStage++;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Finished continent generation");
	}
}

/**
 * @brief Generates forests on the map based on ForestPercentage.
 *
 * Populates the map with forest tiles after continents are formed.
 * Requires a map initialized with water and continents, and CurrentStage set to forest generation.
 */
void AMapGenerator::GenerateForest()
{
	// Find a plain tile for forest generation
	int32 TileIndex = Map->GetRandomTileIndexOfType(ETileType::Plain);
	if (TileIndex == -1)
	{
		CurrentStage++;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Failed to find plain tile for forest generation");
		return;
	}
	
	int32 TotalTiles = static_cast<int32>(std::round((Map->GetTileListLength() * (GroundPercentage / 100.0f) * (ForestPercentage / 100.0f)) / TotalForests));
	int32 TilesGenerated = 0;

	while (TilesGenerated < TotalTiles)
	{
		ATile* Tile = Map->GetTileAtIndex(TileIndex);
		if (Tile->IsTileType(ETileType::Plain)) {
			Tile->ChangeType(Map->TileSet->Forest);
			TilesGenerated++;
		}
		
		TArray<int32> NeighboringTiles = Map->GetNeighboringTiles(TileIndex);
		TileIndex = NeighboringTiles[FMath::RandRange(0, NeighboringTiles.Num() - 1)];
		
		for (auto NeighboringTile : NeighboringTiles)
		{
			if (FMath::RandRange(1, 10) < 2)
			{
				ATile* NeighboringTileObj = Map->GetTileAtIndex(NeighboringTile);
				if (NeighboringTileObj->IsTileType(ETileType::Plain)) {
					NeighboringTileObj->ChangeType(Map->TileSet->Forest);
					TilesGenerated++;
				}
			}
		}
	}
	
	// Move on to the next forest
	ForestsGenerated++;
	
	if (ForestsGenerated >= TotalForests)
	{
		CurrentStage++;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Finished forest generation. Total forests: %d"), TotalForests));
	}
}

/**
 * @brief Generates swamp tiles on the map by converting water tiles adjacent to plain tiles.
 *
 * Calculates the total number of swamp tiles to be generated based on the map size and the provided
 * swamp-specific parameters. Swamp generation starts by finding a water tile adjacent to at least
 * one plain tile. Starting from this tile, additional swamp tiles are created by spreading to
 * neighboring tiles, with a random chance to extend the swamp to adjoining tiles.
 *
 * Tracks the number of swamps generated (`SwampsGenerated`) and advances to the next generation stage
 * when all swamps have been generated. Displays a debug message indicating completion of swamp generation.
 */
void AMapGenerator::GenerateSwamp()
{
	int32 TileIndex = -1;
	bool bFoundStartingTile = false;
	
	// Calculate total tiles for swamps
	int32 TotalTiles = static_cast<int32>(std::round((Map->GetTileListLength() * (GroundPercentage / 100.0f) * (SwampPercentage / 100.0f)) / TotalSwamps));
	int32 TilesGenerated = 0;
	
	int32 KillCounter = 0;
	
	// Find a starting tile for swamp
	while (!bFoundStartingTile)
	{
		KillCounter++;
		if (KillCounter > 10000)
		{
			break;
		}
		
		int32 RandomIndex = Map->GetRandomTileIndexOfType(ETileType::Water);
		TArray<int32> NeighboringTiles = Map->GetNeighboringTiles(RandomIndex);
		int32 NeighboringPlains = 0;
		for (auto NeighboringTile : NeighboringTiles)
		{
			ATile* NeighboringTileObj = Map->GetTileAtIndex(NeighboringTile);
			if (NeighboringTileObj->IsTileType(ETileType::Plain)) {
				NeighboringPlains++;
				break;
			}
		}
		
		if (NeighboringPlains >= 1)
		{
			bFoundStartingTile = true;
			TileIndex = RandomIndex;
			break;
		}
	}
	
	KillCounter = 0;
	
	// Generate swamp
	while (TilesGenerated < TotalTiles)
	{
		KillCounter++;
		if (KillCounter > 100000) { break; }
		
		// Change base tile to swamp
		ATile* Tile = Map->GetTileAtIndex(TileIndex);
		if (!Tile->IsTileType(ETileType::Water))
		{
			Tile->ChangeType(Map->TileSet->Swamp);
			TilesGenerated++;			
		}
		
		TArray<int32> NeighboringTiles = Map->GetNeighboringTiles(TileIndex);
		TileIndex = NeighboringTiles[FMath::RandRange(0, NeighboringTiles.Num() - 1)];
		
		// Randomly change neighbors to swamp
		for (auto NeighboringTile : NeighboringTiles)
		{
			if (FMath::RandRange(1, 10) < 3)
			{
				ATile* NeighboringTileObj = Map->GetTileAtIndex(NeighboringTile);
				if (!NeighboringTileObj->IsTileType(ETileType::Water))
				{
					NeighboringTileObj->ChangeType(Map->TileSet->Swamp);
					TilesGenerated++;					
				}
			}
		}
	}
	
	// Move on to the next swamp
	SwampsGenerated++;
	
	// Finish swamp generation
	if (SwampsGenerated >= TotalSwamps)
	{
		CurrentStage++;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Finished swamp generation. Total swamps: %d"), TotalSwamps));
	}
}

/**
 * @brief Generates a single mountain range by converting plain tiles to mountain tiles.
 *
 * Calculates the number of tiles required for a mountain range based on the map size,
 * ground percentage, mountain percentage, and total number of mountain ranges to be generated.
 * Starts from a random plain tile and progressively changes neighboring tiles to mountain
 * until the target number of tiles for the current mountain range is reached.
 *
 * Skips tiles that are already water or mountain type. Iteratively selects neighboring tiles
 * for the next step of generation, ensuring a contiguous formation of mountains.
 *
 * Increments the MountainRangesGenerated counter after completing a single mountain range.
 * Once all mountain ranges are generated, progresses the generation to the next stage.
 */
void AMapGenerator::GenerateMountainRange()
{
	// Calculate total tiles for mountain ranges
	int32 TotalTiles = static_cast<int32>(std::round((Map->GetTileListLength() * (GroundPercentage / 100.0f) * (MountainPercentage / 100.0f)) / TotalMountainRanges));
	int32 TilesGenerated = 0;
	
	// Get starting tile index
	int32 TileIndex = Map->GetRandomTileIndexOfType(ETileType::Plain);
	
	// Generate mountain range
	while (TilesGenerated < TotalTiles)
	{
		// Change tile to mountain
		ATile* Tile = Map->GetTileAtIndex(TileIndex);
		if (!Tile->IsTileType(ETileType::Water) && !Tile->IsTileType(ETileType::Mountain))
		{
			Tile->ChangeType(Map->TileSet->Mountain);
			MountainTiles.Add(TileIndex);
			TilesGenerated++;
		}
		
		// Get next walker index
		TArray<int32> NeighboringTiles = Map->GetNeighboringTiles(TileIndex);
		TileIndex = NeighboringTiles[FMath::RandRange(0, NeighboringTiles.Num() - 1)];
	}
	
	// Move on to the next mountain range
	MountainRangesGenerated++;
	
	// Finish mountain generation
	if (MountainRangesGenerated >= TotalMountainRanges)
	{
		CurrentStage++;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Finished mountain generation. Total mountain ranges: %d"), TotalMountainRanges));
	}
}

/**
 * @brief Generates hill formations around mountains and on random plain tiles.
 *
 * This method consists of two main steps: First, it surrounds existing mountain tiles
 * with hills to create a smooth transition between terrain types. Second, it randomly
 * generates hill tiles on plain regions based on the specified percentage of ground
 * and hills. The process continues until the desired number of hill tiles is generated
 * for the current stage, after which the hill generation stage is marked as complete.
 *
 * Steps:
 * 1. Surround mountain tiles with hills if not already surrounded.
 * 2. Calculate the total number of hill tiles to generate based on map size and parameters.
 * 3. Randomly spread hill tiles starting from a random plain tile and expanding to neighboring tiles.
 * 4. Increment the stage counter upon finishing the hill generation process.
 *
 * The method uses AMap methods for tile manipulation, including retrieving neighboring tiles
 * and selecting random tiles. Hill generation is proportional to map and hill parameters.
 *
 * @note Hill generation contributes to map terrain diversity and creates terrain transitions.
 */
void AMapGenerator::GenerateHillFormation()
{
	// Surround mountain tiles with hills
	if (!bMountainsSurrounded)
	{
		for (int32 MountainTile : MountainTiles)
		{
			TArray<int32> NeighboringTiles = Map->GetNeighboringTiles(MountainTile);
			for (int32 NeighboringTile : NeighboringTiles)
			{
				ATile* NeighboringTileObj = Map->GetTileAtIndex(NeighboringTile);
				if (NeighboringTileObj->IsTileType(ETileType::Plain))
				{
					NeighboringTileObj->ChangeType(Map->TileSet->Hill);
				}
			}
		}
		
		bMountainsSurrounded = true;
	}
	
	// Calculate total tiles for mountain ranges
	int32 TotalTiles = static_cast<int32>(std::round((Map->GetTileListLength() * (GroundPercentage / 100.0f) * (HillPercentage / 100.0f)) / TotalHills));
	int32 TilesGenerated = 0;
	
	// Get the starting tile
	int32 TileIndex = Map->GetRandomTileIndexOfType(ETileType::Plain);

	int32 KillCounter = 0;
	
	// Generate hill formation
	while (TilesGenerated < TotalTiles)
	{
		KillCounter++;
		if (KillCounter > 100000) { break; }
		
		ATile* Tile = Map->GetTileAtIndex(TileIndex);
		if (Tile->IsTileType(ETileType::Plain))
		{
			Tile->ChangeType(Map->TileSet->Hill);
			TilesGenerated++;
		}
		
		// Get next random walker index
		TArray<int32> NeighboringTiles = Map->GetNeighboringTiles(TileIndex);
		TileIndex = NeighboringTiles[FMath::RandRange(0, NeighboringTiles.Num() - 1)];
	}
	
	// Move on to the next stage
	HillsGenerated++;
	
	// Finish hill generation
	if (HillsGenerated >= TotalHills)
	{
		CurrentStage++;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Finished hill formation. Total hills: %d"), TotalHills));
	}
}
