// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BlonicGameMode.h"
#include "BlonicHUD.h"
#include "BlonicCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABlonicGameMode::ABlonicGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ABlonicHUD::StaticClass();
}
