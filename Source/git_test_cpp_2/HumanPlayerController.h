// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Army.h"
#include "Tile.h"
#include "MyPlayerState.h"
#include "WarlordsGameMode.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/PlayerControllerInterface.h"
#include "UI/MainMapUI.h"
#include "HumanPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GIT_TEST_CPP_2_API AHumanPlayerController : public APlayerController, public IPlayerControllerInterface
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(VisibleAnywhere)
	bool bIsMyTurn = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
	AArmy* SelectedArmy;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	ATile* TargetTile;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	AMyPlayerState* PS;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UMainMapUI* MainMapUI;
	
	UPROPERTY(BlueprintReadWrite, Category = "Game")
	AWarlordsGameMode* GameManager;
	
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	
#pragma region Class References
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class References")
	TSubclassOf<UMainMapUI> MainMapUIClass;
	
#pragma endregion
	
protected:
	virtual void SetupInputComponent() override;
	
	void UpdateTargetTile();
	
	void LeftClick();
	void RightClick();
	
	void SelectArmy(AArmy* InArmy);
	void DeselectArmy();
	
#pragma region Turn System
	
	virtual void StartTurn_Implementation() override;
	
	UFUNCTION()
	void NextTurn();
	
#pragma endregion
	
#pragma region Army Control
	
	void MoveSelectedArmy(ATile* InTile);
	
#pragma endregion
	
public:
	
};
