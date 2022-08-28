// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealWebsocketGameMode.h"
#include "UnrealWebsocketCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealWebsocketGameMode::AUnrealWebsocketGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
