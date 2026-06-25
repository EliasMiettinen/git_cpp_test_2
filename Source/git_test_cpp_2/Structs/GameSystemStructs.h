#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "git_test_cpp_2/Enums.h"
#include "git_test_cpp_2/FactionData.h"
#include "GameSystemStructs.generated.h"

USTRUCT(BlueprintType)
struct FNewGamePlayerData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	bool bIsHuman;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	EFaction Faction;
};

USTRUCT(BlueprintType)
struct FNewGameData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "New Game Data")
	TArray<FNewGamePlayerData> Players;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "New Game Data")
	int32 MapSizeX = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "New Game Data")
	int32 MapSizeY = 0;
};

/**
 *
 *
 */
USTRUCT(BlueprintType)
struct FFactionTableRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
	FText DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
	EFaction Faction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
	UFactionData* Data;
};
