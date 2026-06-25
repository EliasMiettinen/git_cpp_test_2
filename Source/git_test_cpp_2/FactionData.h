#pragma once
#include "UnitData.h"
#include "Engine/DataTable.h"
#include "Structs/GameplayDataStructs.h"
#include "FactionData.generated.h"

class ACity;
enum class EFaction : uint8;

UCLASS(BlueprintType)
class GIT_TEST_CPP_2_API UFactionData : public UDataAsset
{
	
public:
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
	FText DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
	EFaction Faction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
	TSubclassOf<ACity> CityClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
	TArray<UUnitData*> Units;
};
