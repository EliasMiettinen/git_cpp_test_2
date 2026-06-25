// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyNavigator.h"


// Sets default values for this component's properties
UArmyNavigator::UArmyNavigator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UArmyNavigator::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UArmyNavigator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


/**
 * Calculates a path from a starting tile to a target tile using a greedy algorithm
 * that selects the neighboring tile closest to the target until the target is reached.
 *
 * @param Start The starting tile of the path.
 * @param Target The target tile to which the path should lead.
 * @return An array of tiles representing the path from the Start tile to the Target tile.
 *         The path may include the same tile multiple times if no valid path exists.
 */
TArray<ATile*> UArmyNavigator::GetPath(ATile* Start, ATile* Target)
{
	TArray<ATile*> Path;
	
	// Path.Add(Start);
	// Path.Add(Target);
	
	ATile* CurrentTile = Start;
	bool bFoundTarget = false;

	while (!bFoundTarget)
	{
		TArray<ATile*> NeighboringTiles = CurrentTile->GetNeighboringTiles();
		
		ATile* ClosestTile = CurrentTile;		
		Path.Add(CurrentTile);
		for (ATile* NeighboringTile : NeighboringTiles)
		{
			if (FVector::Distance(NeighboringTile->GetActorLocation(), Target->GetActorLocation()) < FVector::Distance(ClosestTile->GetActorLocation(), Target->GetActorLocation()))
			{
				ClosestTile = NeighboringTile;
			}
			
			// If target tile is found, set flag and break
			if (NeighboringTile == Target)
			{
				ClosestTile = Target;
				Path.Add(Target);
				bFoundTarget = true;
				break;
			}
		}
		// Update the current tile
		CurrentTile = ClosestTile;
		
		// If target was found
		bFoundTarget = CurrentTile == Target;
	}
	
	return Path;
}

TArray<ATile*> UArmyNavigator::RetracePath(ATile* Start, ATile* Target)
{
	TArray<ATile*> Path;
	ATile* CurrentTile = Target;
	
	while (CurrentTile != Start)
	{
		Path.Add(CurrentTile);
		// CurrentTile = CurrentTile->GetParent();
	}
	
	return Path;
}
