#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "GameFramework/Actor.h"
#include "Map.generated.h"

UCLASS()
class GIT_TEST_CPP_2_API AMap : public AActor
{
	GENERATED_BODY()
public:
	AMap();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	TArray<ATile*> Tiles;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	int32 SizeX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	int32 SizeY;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	UTileSet* TileSet;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Map")
	void AddTile(ATile* Tile);
	
	UFUNCTION(BlueprintCallable, Category = "Map")
	ATile* GetTileAtIndex(int32 Index);
	
	UFUNCTION(BlueprintCallable, Category = "Map")
	TArray<int32> GetNeighboringTiles(int32 Index);
	
	UFUNCTION(BlueprintCallable, Category = "Map")
	int32 GetRandomTileIndex();
	
	UFUNCTION(BlueprintCallable, Category = "Map")
	int32 GetRandomTileIndexOfType(ETileType InType);
	
	UFUNCTION(BlueprintCallable, Category = "Map")
	void SetMapSize(int32 NewSizeX, int32 NewSizeY);
	
#pragma region Utility Functions
	
	UFUNCTION(BlueprintCallable, Category = "Map")
	int32 GetTileListLength();
	
	bool IsBorderTile(int32 Index, int32 Modifier = 0);
	
	bool IsTileWithinBounds(int32 Index);
	
	bool IsTileInEvenRow(int32 Index);
	
#pragma endregion
};
