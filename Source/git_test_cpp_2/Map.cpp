#include "Map.h"

// Sets default values
AMap::AMap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AMap::BeginPlay()
{
	Super::BeginPlay();
}

/**
 * Add a new tile to the map, and by default, set its type to water.
 * @param Tile 
 */
void AMap::AddTile(ATile* Tile)
{
	if (Tile)
	{
		Tile->ChangeType(TileSet->Water);
		Tiles.Add(Tile);
	}
}

/**
 * Get a random tile from the map.
 * @return A random tile, or nullptr if the map is empty.
 */
ATile* AMap::GetRandomTile()
{
	if (Tiles.Num() == 0)
	{
		return nullptr;
	}

	int32 RandomIndex = FMath::RandRange(0, Tiles.Num() - 1);
	return Tiles[RandomIndex];
}

int32 AMap::GetTileListLength()
{
	return Tiles.Num();
}
