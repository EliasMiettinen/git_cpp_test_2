#pragma once

#include "CoreMinimal.h"
#include "ArmyNavigator.h"
#include "Components/ActorComponent.h"
#include "ArmyMovementComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GIT_TEST_CPP_2_API UArmyMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UArmyMovementComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MovementSpeed = 1000.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RotationSpeed = 1000.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DistanceThreshold = 1.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	int32 MovementPoints;
	
protected:
	
	AArmy* Army;
	UArmyNavigator* Navigator;
	
	virtual void OnRegister() override;
	virtual void BeginPlay() override;
	
private:
	TArray<ATile*> Path;
	
	bool bMoving;
	ATile* CurrentTarget;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void Move(ATile* Tile);
	
	void CalculateMovementPoints();
	
	bool IsMoving() const { return bMoving; }
};
