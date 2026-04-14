// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "TileSet.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class GIT_TEST_CPP_2_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	ETileType Type;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Tile")
	bool IsTileType(ETileType InType);
	
	UFUNCTION(BlueprintCallable, Category = "Tile")
	bool IsTileTypes(TArray<ETileType> InTypes);
	
	UFUNCTION(BlueprintCallable, Category = "Tile")
	void ChangeType(UTileData* NewTileData);
};
