#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"

UENUM(BlueprintType)
enum class ETileType : uint8
{
	Plain		UMETA(DisplayName = "Plain"),
	Forest		UMETA(DisplayName = "Forest"),
	Mountain	UMETA(DisplayName = "Mountain"),
	Hill		UMETA(DisplayName = "Hill"),
	Swamp		UMETA(DisplayName = "Swamp"),
	Water		UMETA(DisplayName = "Water"),
};

UENUM(BlueprintType)
enum class EFaction : uint8
{
	Vikings		UMETA(DisplayName = "Vikings"),
	Franks		UMETA(DisplayName = "Franks"),
};
