// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapGenerator.h"
#include "GameFramework/GameModeBase.h"
#include "Structs/GameSystemStructs.h"
#include "WarlordsGameMode.generated.h"



UCLASS()
class GIT_TEST_CPP_2_API AWarlordsGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AWarlordsGameMode();
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Game")
	TArray<AController*> Players;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Game")
	int32 CurrentTurn = -1;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Game")
	int32 TurnId = 0;
	
protected:
	virtual void BeginPlay() override;
	void InitializeAIPlayers(TArray<FNewGamePlayerData> Players);
	void OnAllPlayersReady();
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Game")
	AMapGenerator* MapGenerator;
	
public:
	
#pragma region Turn System
	
	UFUNCTION()
	void NextTurn();
	
	UFUNCTION()
	void EnableTurnForPlayer();
	
#pragma endregion
	
#pragma region Game Initialization
	
	void InitializeNewGame();
	
	UFUNCTION()
	void OnMapGenerationComplete();
	
#pragma endregion
	
};
