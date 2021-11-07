// Copyright Epic Games, Inc. All Rights Reserved.

#include "PZGameMode.h"
#include "PZCharacter.h"
#include "UObject/ConstructorHelpers.h"

APZGameMode::APZGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
