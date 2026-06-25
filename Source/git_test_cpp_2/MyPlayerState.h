// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "City.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GIT_TEST_CPP_2_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 Id;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	FString PlayerName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	EFaction Faction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TArray<ACity*> Cities;
	
protected:
	
public:
	
#pragma region Utility Functions
	
	void AddCity(ACity* City);
	
#pragma endregion
	
};
