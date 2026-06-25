// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Structs/GameSystemStructs.h"
#include "WarlordsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GIT_TEST_CPP_2_API UWarlordsGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	virtual void Init() override;
	virtual void Shutdown() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	bool bIsNewGame;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	FNewGameData NewGameData;
	
protected:
	
public:
	
	FNewGameData GetNewGameData();
	
};
