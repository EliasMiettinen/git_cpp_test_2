// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "Components/ActorComponent.h"
#include "ArmyNavigator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GIT_TEST_CPP_2_API UArmyNavigator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UArmyNavigator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	TArray<ATile*> GetPath(ATile* Start, ATile* Target);
	
	TArray<ATile*> RetracePath(ATile* Start, ATile* Target);
};