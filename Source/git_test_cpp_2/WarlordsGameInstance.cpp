// Fill out your copyright notice in the Description page of Project Settings.


#include "WarlordsGameInstance.h"

void UWarlordsGameInstance::Init()
{
	Super::Init();
	
	FNewGameData Data;
	
	FNewGamePlayerData HumanPlayer;
	HumanPlayer.Name = "Harald I";
	HumanPlayer.Faction = EFaction::Vikings;
	HumanPlayer.bIsHuman = true;
	Data.Players.Add(HumanPlayer);
	
	FNewGamePlayerData AI1Player;
	AI1Player.Name = "AI IV";
	AI1Player.Faction = EFaction::Franks;
	AI1Player.bIsHuman = false;
	Data.Players.Add(AI1Player);
	
	Data.MapSizeX = 24;
	Data.MapSizeY = 24;
	
	bIsNewGame = true;
	this->NewGameData = Data;
}

void UWarlordsGameInstance::Shutdown()
{
	Super::Shutdown();
}

FNewGameData UWarlordsGameInstance::GetNewGameData()
{
	return this->NewGameData;
}

