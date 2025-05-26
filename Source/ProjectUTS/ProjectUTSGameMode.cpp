// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectUTSGameMode.h"
#include "ProjectUTSCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectUTSGameMode::AProjectUTSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
