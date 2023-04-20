// Copyright Epic Games, Inc. All Rights Reserved.

#include "JuegoMusicaGameMode.h"
#include "JuegoMusicaCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJuegoMusicaGameMode::AJuegoMusicaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
