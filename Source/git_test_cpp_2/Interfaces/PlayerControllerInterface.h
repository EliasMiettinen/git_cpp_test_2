#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerControllerInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class GIT_TEST_CPP_2_API UPlayerControllerInterface : public UInterface
{
	GENERATED_BODY()
};

class GIT_TEST_CPP_2_API IPlayerControllerInterface
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PlayerController")
	void StartTurn();
};
