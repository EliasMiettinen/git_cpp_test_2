// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"

#include "City.h"


#pragma region Utility Functions

void AMyPlayerState::AddCity(ACity* City)
{
	Cities.Add(City);
}

#pragma endregion
