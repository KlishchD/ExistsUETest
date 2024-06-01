// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExistsUETestGameMode.h"
#include "ExistsUETestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AExistsUETestGameMode::AExistsUETestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
