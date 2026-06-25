// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WarlordsGameMode.h"
#include "Interfaces/PlayerControllerInterface.h"
#include "AIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GIT_TEST_CPP_2_API AAIPlayerController : public AAIController, public IPlayerControllerInterface
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
public:
	
	UPROPERTY(VisibleAnywhere)
	bool bIsMyTurn;
	
#pragma region References
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	AMyPlayerState* PS;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	AWarlordsGameMode* GameManager;
	
#pragma endregion
	
#pragma region Turn System
	virtual void StartTurn_Implementation() override;
	
	UFUNCTION()
	void NextTurn();
	
#pragma endregion
	
private:
	FTimerHandle TestTurnTimer;
	
};
