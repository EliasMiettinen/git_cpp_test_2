#pragma once
#include "ArmyMovementComponent.h"
#include "ArmyNavigator.h"
#include "Tile.h"
#include "Structs/GameplayDataStructs.h"
#include "Army.generated.h"

UCLASS()
class GIT_TEST_CPP_2_API AArmy : public AActor
{
public:
	GENERATED_BODY()

	// Constructor
	AArmy();
	
	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* SelectionMarker;
	
	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Army")
	int32 OwnerId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Army")
	TArray<FUnit> Units;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Army")
	ATile* Tile;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selection")
	bool bIsSelected;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int32 MovementPoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview")
	int32 CurrentPreviewUnitIndex;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview")
	AUnitPreview* PreviewUnit;
	
#pragma region Components
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UArmyNavigator* Navigator;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UArmyMovementComponent* Movement;
	
#pragma endregion
	
protected:
	
	virtual void BeginPlay() override;
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "Selection")
	void Select();
	
	UFUNCTION(BlueprintCallable, Category = "Selection")
	void Deselect();
	
	UFUNCTION(BlueprintCallable, Category = "Management")
	void AddUnit(FUnit Unit);
	
	UFUNCTION(BlueprintCallable, Category = "Management")
	void RemoveUnit(int32 Index);
	
	UFUNCTION(BlueprintCallable, Category = "Management")
	void UpdateTile(ATile* NewTile);
	
	UFUNCTION(BlueprintCallable, Category = "Management")
	void UpdatePreviewUnit(int32 Index);
	
#pragma region Actions
	
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void Move(ATile* TargetTile);

#pragma endregion
	
};