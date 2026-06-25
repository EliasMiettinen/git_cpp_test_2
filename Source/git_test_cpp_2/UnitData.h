#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "UnitPreview.h"
#include "UnitData.generated.h"

UCLASS(BlueprintType)
class GIT_TEST_CPP_2_API UUnitData : public UDataAsset
{
public:
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	FString DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	EFaction Faction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	int32 MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	int32 MaxMovementPoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	float AttackDamage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	int32 Armor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	float Strength;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	UTexture2D* Icon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
	TSubclassOf<AUnitPreview> PreviewClass;
	
};
