// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPlayerController.h"
#include "Kismet/GameplayStatics.h"

void AAIPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	PS = Cast<AMyPlayerState>(PlayerState);
	GameManager = Cast<AWarlordsGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

#pragma region Player Controller

void AAIPlayerController::StartTurn_Implementation()
{
	bIsMyTurn = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "AI Player Controller Start Turn");
	
	// Set the timer to call NextTurn after 5 seconds
	GetWorld()->GetTimerManager().SetTimer(TestTurnTimer, this, &AAIPlayerController::NextTurn, 5.0f, false);
}

void AAIPlayerController::NextTurn()
{
	bIsMyTurn = false;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "AI Player Controller Next Turn");
	
	// Pass the turn to the next player
	if (GameManager) GameManager->NextTurn();
	
}

#pragma endregion
