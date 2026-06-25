#pragma once
#include "CoreMinimal.h"
#include "git_test_cpp_2/UnitPreview.h"
#include "GameplayDataStructs.generated.h"

USTRUCT(BlueprintType)
struct FUnit
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	float Health = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	float MaxHealth = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	int32 MovementPoints = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	int32 MaxMovementPoints = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float AttackDamage = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Armor = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Strength = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	UTexture2D* Icon = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	TSubclassOf<AUnitPreview> PreviewClass;
};
