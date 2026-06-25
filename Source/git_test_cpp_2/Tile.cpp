// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Map.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATile::ATile()
{
	// Disable ticking
	PrimaryActorTick.bCanEverTick = false;
	
	// Set up root component
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	// Set up mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(Root);
	SpawnPoint->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));
	
	// Setup utilities
	Construct = nullptr;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
	// Get the reference to map
	Map = Cast<AMap>(UGameplayStatics::GetActorOfClass(GetWorld(), AMap::StaticClass()));
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**
 * Is the tile of a specified type?
 * @param InType 
 * @return 
 */
bool ATile::IsTileType(ETileType InType)
{
	return this->Type == InType;
}


/**
 * Is tile one of the specified types
 * @param InTypes 
 * @return 
 */
bool ATile::IsTileTypes(TArray<ETileType> InTypes)
{
	return InTypes.Contains(this->Type);
}

void ATile::ChangeType(UTileData* NewTileData)
{
	if (NewTileData)
	{
		this->Type = NewTileData->Type;
		this->Mesh->SetStaticMesh(NewTileData->TileMesh);
	}
}

/**
 * Returns the location of the spawn point
 * Used to spawn cities, ruins, units, etc. on the tile 
 * @return 
 */
FVector ATile::GetTargetPointLocation()
{
	return SpawnPoint->GetComponentLocation();
}


/**
 * Gets adjacent tiles from the map.
 *
 * @return Array of neighboring tile pointers, or empty if tile not in map.
 */
TArray<ATile*> ATile::GetNeighboringTiles()
{
	TArray<ATile*> NeighboringTiles;
	
	if (Map)
	{
		// Get the index of this tile
		int32 Index = Map->IndexOf(this);
		if (Index == -1) return NeighboringTiles;
		
		// Get neighboring tile index's
		TArray<int32> NeighboringIndex = Map->GetNeighboringTiles(Index);
		
		// Get the ATile* objects with the IDs and add them to the array
		for (int32 NI : NeighboringIndex)
		{
			NeighboringTiles.Add(Map->GetTileAtIndex(NI));
		}
	}
	
	// Return the array of neighboring tiles (ATile*)
	return NeighboringTiles;
}


