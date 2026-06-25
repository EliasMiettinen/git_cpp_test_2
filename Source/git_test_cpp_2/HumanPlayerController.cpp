// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanPlayerController.h"
#include "Tile.h"
#include "Army.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MainMapUI.h"

void AHumanPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	PS = Cast<AMyPlayerState>(PlayerState);
	GameManager = Cast<AWarlordsGameMode>(UGameplayStatics::GetGameMode(this));
	
	// Initialize the main UI or the player
	if (MainMapUIClass && !MainMapUI)
	{
		MainMapUI = CreateWidget<UMainMapUI>(this, MainMapUIClass);
		if (MainMapUI)
		{
			MainMapUI->AddToViewport();
			MainMapUI->OnNextTurnClicked.AddDynamic(this, &AHumanPlayerController::NextTurn);
		}
	}
}

void AHumanPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Only if it's the player's turn
	if (!bIsMyTurn) return;
	
	// Update target tile based on player's cursor position
	UpdateTargetTile();
}

void AHumanPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// Set up input mode
	bShowMouseCursor = true;
	SetInputMode(FInputModeGameAndUI());
	
	// Assign input actions
	if (InputComponent)
	{
		InputComponent->BindAction("LeftMouseButton", IE_Pressed, this, &AHumanPlayerController::LeftClick);
		InputComponent->BindAction("RightMouseButton", IE_Pressed, this, &AHumanPlayerController::RightClick);
	}
}
/**
 * Updates TargetTile based on the tile under the mouse cursor using a line trace.
 * Called in Tick to continuously track the mouse position. Sets TargetTile to the
 * hit tile actor or nullptr if no tile is detected. Uses ECC_WorldStatic channel.
 */
void AHumanPlayerController::UpdateTargetTile()
{
	// Calculate the location and direction of the mouse cursor
	FVector MouseWorldLocation;
	FVector MouseWorldDirection;
	
	DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);
	FVector TraceEndLocation = MouseWorldLocation + MouseWorldDirection * 10000.0f;
	
	// Do the line trace to find the target tile
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, MouseWorldLocation, TraceEndLocation, ECC_WorldStatic))
	{
		// If hit actor is a valid tile
		if ( HitResult.GetActor()->IsA(ATile::StaticClass()))
		{
			TargetTile = Cast<ATile>(HitResult.GetActor());
		}
		else
		{
			TargetTile = nullptr;
		}
	}
	else
	{
		TargetTile = nullptr;
	}
}

void AHumanPlayerController::LeftClick()
{
	if (!bIsMyTurn) return;
	if (TargetTile == nullptr) return;
	
	// Deselect the currently selected army by default
	DeselectArmy();
	// If tile contains army, select it
	if (TargetTile->Army)
	{
		SelectArmy(TargetTile->Army);
	}
}

void AHumanPlayerController::RightClick()
{
	if (!bIsMyTurn) return;
	if (SelectedArmy == nullptr || TargetTile == nullptr) return;
	
	MoveSelectedArmy(TargetTile);
}

#pragma region Turn System

/**
 * Called from Game Mode when it's this player's turn
 * 
 * Inherited from generic player controller interface containing mutual functions shared by all players
 */
void AHumanPlayerController::StartTurn_Implementation()
{
	bIsMyTurn = true;
	MainMapUI->OnEnableTurn();
}

/**
 * Passes the turn to the next player
 * Bound to the next turn event from UI
 */
void AHumanPlayerController::NextTurn()
{
	if (!bIsMyTurn) return;
	
	bIsMyTurn = false;
	
	// Disable UI control during another player's turns
	MainMapUI->OnEndTurn();
	
	DeselectArmy();
	
	// Pass turn to the next player
	GameManager->NextTurn();
	
	// Start moving all the required armies along the path and everything else that has to be done before next player starts their turn
}

#pragma endregion

#pragma region Army Control

void AHumanPlayerController::SelectArmy(AArmy* InArmy)
{
	// Validation
	if (InArmy == nullptr) return;
	if (InArmy->OwnerId != PS->Id)
		return;
	
	// Deselect the currently selected army
	if (SelectedArmy)
		SelectedArmy->Deselect();
	
	// Select the army
	InArmy->Select();
	SelectedArmy = InArmy;
	// TODO: Later on, should also update UI army panel
}

void AHumanPlayerController::DeselectArmy()
{
	if (SelectedArmy)
		SelectedArmy->Deselect();
	
	SelectedArmy = nullptr;
}

void AHumanPlayerController::MoveSelectedArmy(ATile* InTile)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Moviasdasdasdaasdsdang army %s to %s"), *SelectedArmy->GetName(), *InTile->GetName()));
	
	if (SelectedArmy == nullptr) return;  
	if (InTile == nullptr) return;
	if (SelectedArmy->Tile == InTile) return;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Moving army %s to %s"), *SelectedArmy->GetName(), *InTile->GetName()));
	SelectedArmy->Move(InTile);
}

#pragma endregion


