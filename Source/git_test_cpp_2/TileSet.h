#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "Engine/DataAsset.h"
#include "TileSet.generated.h"

/**
 * Tile Data
 */
UCLASS(BlueprintType)
class UTileData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tile")
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tile")
	int32 EnterCost;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tile")
	ETileType Type;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tile")
	UStaticMesh* TileMesh;
};

/**
 * Tile Set Data
 */
UCLASS(BlueprintType)
class UTileSet : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TileSet")
	FName Name;
	
	// Tile types
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TileSet")
	UTileData* Plain;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TileSet")
	UTileData* Forest;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TileSet")
	UTileData* Hill;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TileSet")
	UTileData* Mountain;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TileSet")
	UTileData* Swamp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TileSet")
	UTileData* Water;
};
