#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnitPreview.generated.h"

UCLASS()
class GIT_TEST_CPP_2_API AUnitPreview : public AActor
{
public:
	
	GENERATED_BODY()
	
	AUnitPreview();
	
#pragma region Components
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;
	
#pragma endregion
	
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	
	virtual void BeginPlay() override;
	
public:
	
};
