// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TicGameMode.h"
#include "TicPlayerController.h"
#include "TicPawn.h"

ATicGameMode::ATicGameMode()
{
	// no pawn by default
	DefaultPawnClass = ATicPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ATicPlayerController::StaticClass();
}
