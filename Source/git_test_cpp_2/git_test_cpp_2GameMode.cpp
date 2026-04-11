// Copyright Epic Games, Inc. All Rights Reserved.

#include "git_test_cpp_2GameMode.h"
#include "git_test_cpp_2Character.h"
#include "UObject/ConstructorHelpers.h"

Agit_test_cpp_2GameMode::Agit_test_cpp_2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
