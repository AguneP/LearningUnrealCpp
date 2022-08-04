// Copyright Epic Games, Inc. All Rights Reserved.

#include "EstudoCPPGameMode.h"
#include "EstudoCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEstudoCPPGameMode::AEstudoCPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
