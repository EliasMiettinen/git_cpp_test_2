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
 * Find a tile at a given index.
 * @param Index 
 * @return The tile at the specified index, or nullptr if out of bounds.
 */
ATile* AMap::GetTileAtIndex(int32 Index)
{
	if (Index < 0 || Index >= Tiles.Num())
	{
		return nullptr;
	}
	return Tiles[Index];
}

/**
 * Get a random tile from the map.
 * @return A random tile, or nullptr if the map is empty.
 */
int32 AMap::GetRandomTileIndex()
{
	if (Tiles.Num() == 0)
	{
		return -1;
	}

	int32 RandomIndex = FMath::RandRange(0, Tiles.Num() - 1);
	return RandomIndex;
}

/**
 * Get a random tile of a specific type from the map.
 * @param InType The type of tile to get.
 * @return The index of a random tile of the specified type, or -1 if none found.
 */
int32 AMap::GetRandomTileIndexOfType(ETileType InType)
{
	int32 Counter = 0;
	
	while (Counter < Tiles.Num())
	{
		int32 RandomIndex = FMath::RandRange(0, Tiles.Num() - 1);
		ATile* Tile = Tiles[RandomIndex];
		if (Tile->IsTileType(InType))
		{
			return RandomIndex;
		}
		Counter++;
	}
	return -1;
}

/**
 * Get the neighboring tiles of a given tile index.
 * @param Index The index of the tile to get neighbors for.
 * @return An array of neighboring tile indices.
 */
TArray<int32> AMap::GetNeighboringTiles(int32 Index)
{
	TArray<int32> NeighboringTiles;
	
	// Left tile
	int32 LeftTileIndex = Index - 1;
	if (LeftTileIndex >= 0 && !IsBorderTile(Index, 0))
	{
		NeighboringTiles.Add(LeftTileIndex);
	}
	
	// Right tile
	int32 RightTileIndex = Index + 1;
	if (RightTileIndex < Tiles.Num() && !IsBorderTile(Index, 1))
	{
		NeighboringTiles.Add(RightTileIndex);
	}
	
	// Top right tile
	int32 TopRightTileIndex = Index + SizeX + 1;
	if (IsTileWithinBounds(TopRightTileIndex - 1))
	{
		if (IsTileInEvenRow(Index))
		{
			if (!IsBorderTile(Index, 1))
			{
				NeighboringTiles.Add(TopRightTileIndex);
			}
		} 
		else
		{
			NeighboringTiles.Add(TopRightTileIndex - 1);
		}
	}
	
	// Bottom right tile
	int32 BottomRightTileIndex = IsTileInEvenRow(Index) ? (Index - SizeX + 1) : (Index - SizeX);
	if (IsTileWithinBounds(Index - SizeX))
	{
		if (IsTileInEvenRow(Index))
		{
			if (!IsBorderTile(Index, 1))
			{
				NeighboringTiles.Add(BottomRightTileIndex);
			}
		}
		else
		{
			NeighboringTiles.Add(BottomRightTileIndex);
		}
	}
	
	// Top left tile
	int32 TopLeftTileIndex = !IsTileInEvenRow(Index) ? (Index + SizeX - 1) : (Index + SizeX);
	if (IsTileWithinBounds(Index + SizeX))
	{
		if (!IsTileInEvenRow(Index))
		{
			if (!IsBorderTile(Index, 0))
			{
				NeighboringTiles.Add(TopLeftTileIndex);
			}
		}
		else
		{
			NeighboringTiles.Add(TopLeftTileIndex);
		}
	}
	
	// Bottom left tile
	int32 BottomLeftTileIndex = !IsTileInEvenRow(Index) ? (Index - SizeX - 1) : (Index - SizeX);
	if (IsTileWithinBounds(Index - SizeX))
	{
		if (!IsTileInEvenRow(Index))
		{
			if (!IsBorderTile(Index, 0))
			{
				NeighboringTiles.Add(BottomLeftTileIndex);
			}
		}
		else
		{
			NeighboringTiles.Add(BottomLeftTileIndex);
		}
	}
	
	// Finally, return all compatible tiles
	return NeighboringTiles;
}

/**
 * Update map dimensions
 * @param NewSizeX 
 * @param NewSizeY 
 */
void AMap::SetMapSize(int32 NewSizeX, int32 NewSizeY)
{
	this->SizeX = NewSizeX;
	this->SizeY = NewSizeY;
}

#pragma region Utility Functions

/**
 * Return total number of tiles in the map
 * @return
 */
int32 AMap::GetTileListLength()
{
	return Tiles.Num();
}

/**
 * Check if a tile in a given index is on the border of the map
 * @param Index 
 * @param Modifier 
 * @return 
 */
bool AMap::IsBorderTile(int32 Index, int32 Modifier)
{
	return (Index + Modifier) % SizeX == 0;
}

/**
 * Check if a tile in a given index is within map bounds
 * @param Index 
 * @return 
 */
bool AMap::IsTileWithinBounds(int32 Index)
{
	return Index >= 0 && Index < Tiles.Num();
}

/**
 * Check if a tile in a given index is in an even row
 * @param Index 
 * @return 
 */
bool AMap::IsTileInEvenRow(int32 Index)
{
	return (Index / SizeX) % 2 == 0;
}
#pragma endregion
