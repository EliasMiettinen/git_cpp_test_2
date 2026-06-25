#include "MainMapUI.h"

void UMainMapUI::NativeConstruct()
{
	Super::NativeConstruct();
}

/**
 * Called from HumanPlayerController when my turn is activated
 * 
 * Enables the UI for the player's turn
 */
void UMainMapUI::OnEnableTurn()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Enable Turn in main UI");
	bEnabled = true;
}

/**
 * Called from HumanPlayerController when my turn is ended
 * 
 * Disables the UI for the player's turn
 */
void UMainMapUI::OnEndTurn()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "End Turn in main UI");
	bEnabled = false;
}

/**
 * Emits the next turn event to the human player controller
 */
void UMainMapUI::NextTurn()
{
	OnNextTurnClicked.Broadcast();
}

