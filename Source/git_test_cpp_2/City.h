// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Army.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "UnitData.h"
#include "Structs/GameplayDataStructs.h"
#include "City.generated.h"

UCLASS()
class GIT_TEST_CPP_2_API ACity : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACity();
	
#pragma region Components
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;
	
#pragma endregion
	
#pragma region City
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "City")
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "City")
	int32 OwnerPlayer;
	
#pragma endregion
	
#pragma region Army / Units
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Army / Units")
	AArmy* Army;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Army / Units")
	TSubclassOf<AArmy> ArmyClass;
	
#pragma endregion
	
#pragma region Tile
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	ATile* Tile;
	
#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void Initialize(ATile* InTile, int32 InOwnerPlayer, FString InName);

	void SpawnUnit(UUnitData* InUnit);
	
	AArmy* GetArmy();
	
	FUnit ConvertUnitDataToUnit(UUnitData* InUnitData);
	
};
