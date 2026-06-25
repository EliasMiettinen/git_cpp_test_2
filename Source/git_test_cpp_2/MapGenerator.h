// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FactionData.h"
#include "Map.h"
#include "MyPlayerState.h"
#include "GameFramework/Actor.h"
#include "TileSet.h"
#include "Engine/DataTable.h"
#include "MapGenerator.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMapGenerationComplete);

UCLASS()
class GIT_TEST_CPP_2_API AMapGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapGenerator();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	AMap* Map;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	TSubclassOf<ATile> TileClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	float DelayBetweenSteps = 0.2f;
	
	UPROPERTY(BlueprintAssignable, Category = "Map")
	FOnMapGenerationComplete OnMapGenerationComplete;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	UDataTable* FactionsTable;

#pragma region Map Settings
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Settings")
	int32 MapSizeX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Settings")
	int32 MapSizeY;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Settings", meta = (UIMin = "0.0", UIMax = "90.0", ClampMin = "0.0", ClampMax = "90.0"))
	float GroundPercentage = 10.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Settings", meta = (UIMin = "10.0", UIMax = "30.0", ClampMin = "10.0", ClampMax = "30.0"))
	float ForestPercentage = 10.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Settings", meta = (UIMin = "0.0", UIMax = "20.0", ClampMin = "0.0", ClampMax = "20.0"))
	float SwampPercentage = 10.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Settings", meta = (UIMin = "5.0", UIMax = "25.0", ClampMin = "5.0", ClampMax = "25.0"))
	float MountainPercentage = 10.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Settings", meta = (UIMin = "5.0", UIMax = "15.0", ClampMin = "5.0", ClampMax = "15.0"))
	float HillPercentage = 10.0f;
	
#pragma endregion
	
#pragma region Generation
	
	bool bIsGenerating = false;
	
	// Used to switch to the next stage of map generation. e.g., from water to ground to forest etc.
	int32 CurrentStage = 0;
	
	float TimeToNextStep = 0;
	
#pragma endregion
	
#pragma region Water Generation
	
	int32 CurrentRow = 1;
	FVector RowPos;
	FVector TilePos;
	
#pragma endregion
	
#pragma region Ground Generation
	
	int32 TotalContinents;
	int32 ContinentsGenerated;
	
#pragma endregion

	
#pragma region Forest Generation
	
	int32 TotalForests;
	int32 ForestsGenerated;
	
#pragma endregion
	
#pragma region Swamp Generation
	
	int32 TotalSwamps;
	int32 SwampsGenerated;
	
#pragma endregion
	
#pragma region Mountain Generation
	
	int32 TotalMountainRanges;
	int32 MountainRangesGenerated;
	TArray<int32> MountainTiles;
	
#pragma endregion
	
#pragma region Hill Generation
	
	int32 TotalHills;
	int32 HillsGenerated;
	bool bMountainsSurrounded;
	
#pragma endregion
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map")
	UTileSet* TileSet;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void NextStep();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void Initialize(int32 SizeX, int32 SizeY);

	UFUNCTION(BlueprintCallable, Category = "Map")
	void GenerateMap();

#pragma region Map Generation
	
	void GenerateWaterRow();
	void GenerateContinent();
	void GenerateForest();
	void GenerateSwamp();
	void GenerateMountainRange();
	void GenerateHillFormation();
	
#pragma endregion
	
#pragma region City Generation
	
	void GenerateStartingCities();
	void SpawnStartupArmy(UFactionData* FactionData, ACity* City);
	void GenerateCities();
	
#pragma endregion
	
	void CompleteGeneration();
};
