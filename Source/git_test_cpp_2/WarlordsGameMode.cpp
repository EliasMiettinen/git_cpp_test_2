// Fill out your copyright notice in the Description page of Project Settings.


#include "WarlordsGameMode.h"

#include "AIPlayerController.h"
#include "HumanPlayerController.h"
#include "MyPlayerState.h"
#include "BasePlayerPawn.h"
#include "MapGenerator.h"
#include "PlayerPawn.h"
#include "WarlordsGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/GameSystemStructs.h"

AWarlordsGameMode::AWarlordsGameMode()
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AHumanPlayerController::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
}

void AWarlordsGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	// Subscribe to map generation complete event
	MapGenerator = Cast<AMapGenerator>(UGameplayStatics::GetActorOfClass(GetWorld(), AMapGenerator::StaticClass()));
	if (MapGenerator)
	{
		MapGenerator->OnMapGenerationComplete.AddDynamic(this, &AWarlordsGameMode::OnMapGenerationComplete);
	}
	
	// Find the game instance
	UWarlordsGameInstance* GI = Cast<UWarlordsGameInstance>(GetGameInstance());
	if (GI)
	{		
		// If should initialize new game
		if (GI->bIsNewGame)
		{
			InitializeNewGame();
		}
	}
}

/**
 * Advances to the next turn, cycling through players. Resets to player 0 
 * and increments TurnId when reaching the end of the player list.
 */
void AWarlordsGameMode::NextTurn()
{
	CurrentTurn++;
	
	if (CurrentTurn >= Players.Num())
	{
		CurrentTurn = 0;
		TurnId++;
	}
	
	EnableTurnForPlayer();
}
 
void AWarlordsGameMode::EnableTurnForPlayer()
{
	AController* PC = Players[CurrentTurn];
	
	if (!PC->Implements<UPlayerControllerInterface>()) return;
	
	// Start turn on the player controller
	IPlayerControllerInterface::Execute_StartTurn(PC);
}

#pragma region Game Initialization

void AWarlordsGameMode::InitializeNewGame()
{
	FNewGameData NewGameData;
	
	UWarlordsGameInstance* GI = Cast<UWarlordsGameInstance>(GetGameInstance());
	if (GI)
	{
		NewGameData = GI->GetNewGameData();
	}
	
	// Initialize player
	AHumanPlayerController* PC = Cast<AHumanPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		// Add human player to player list
		Players.Add(PC);
		
		// Spawn and possess the pawn for the player
		APlayerPawn* PlayerPawn = Cast<APlayerPawn>(PC->GetPawn());
		if (PlayerPawn)
		{
			PlayerPawn->SetActorLocation(FVector(0, 0, 0));
			PlayerPawn->SetActorRotation(FRotator(0, 0, 0));
		}

		
		// Get the player state class and update default information
		AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
		if (PS)
		{
			PS->Id = 0;
			PS->PlayerName = NewGameData.Players[0].Name;
			PS->Faction = NewGameData.Players[0].Faction;
		}
	}
	
	// Set Map dimensions
	MapGenerator->Initialize(NewGameData.MapSizeX, NewGameData.MapSizeY);
	
	// Initialize AI players
	InitializeAIPlayers(NewGameData.Players);
	
	CurrentTurn = 0;
	
	// Move on to the next stage
	OnAllPlayersReady();
}

void AWarlordsGameMode::InitializeAIPlayers(TArray<FNewGamePlayerData> PlayerObjects)
{
	for (FNewGamePlayerData& Data : PlayerObjects)
	{
		// Skip human players
		if (Data.bIsHuman) continue;
		
		// Create AI Controller
		AAIPlayerController* AIController = GetWorld()->SpawnActor<AAIPlayerController>();
		
		// Spawn AI pawn for the controller
		ABasePlayerPawn* AIPawn = GetWorld()->SpawnActor<ABasePlayerPawn>(ABasePlayerPawn::StaticClass());
		
		if (AIController && AIPawn)
		{			
			this->Players.Add(AIController);
			AIController->Possess(AIPawn);
			
			// Get player state class to update information
			AMyPlayerState* PS = GetWorld()->SpawnActor<AMyPlayerState>();
			if (PS)
			{
				AIController->PlayerState = PS;
				
				// Initialize values
				PS->Id = Players.Num() - 1;
				PS->PlayerName = Data.Name;
				PS->Faction = Data.Faction;
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("AI Player Controller has no player state"));
			}
		}
	}
}

void AWarlordsGameMode::OnAllPlayersReady()
{
	MapGenerator->GenerateMap();
}

void AWarlordsGameMode::OnMapGenerationComplete()
{
	// Set player camera on top of their starting city
	AHumanPlayerController* PC = Cast<AHumanPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
		if (PS && PS->Cities.Num() > 0)
		{
			APlayerPawn* PlayerPawn = Cast<APlayerPawn>(PC->GetPawn());
			if (PlayerPawn)
			{
				FVector StartingLocation = PS->Cities[0]->GetActorLocation();
				PlayerPawn->SetActorLocation(StartingLocation);
			}
		}
	}
	
	CurrentTurn = 0;
	EnableTurnForPlayer();
}

#pragma endregion
