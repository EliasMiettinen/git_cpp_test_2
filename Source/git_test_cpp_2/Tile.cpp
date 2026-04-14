// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"


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
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
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

