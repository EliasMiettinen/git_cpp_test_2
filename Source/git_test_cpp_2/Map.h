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
	ATile* GetRandomTile();
	
	UFUNCTION(BlueprintCallable, Category = "Map")
	int32 GetTileListLength();
};
