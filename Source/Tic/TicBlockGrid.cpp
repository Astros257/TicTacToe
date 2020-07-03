// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TicBlockGrid.h"
#include "Kismet/GameplayStatics.h"
#include "TicBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ATicBlockGrid::ATicBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	ScoreText->SetText(FString("X or Y"));
	ScoreText->SetupAttachment(DummyRoot);

	// Set defaults
	Size = 3;
	BlockSpacing = 300.f;
	blocks = new ATicBlock * [Size * Size];
	isX = true;
	hasWon = false;
}


bool ATicBlockGrid::turnStatus()
{
	isX = !isX;
	return isX;
}

void ATicBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	// Number of blocks
	const int32 NumBlocks = Size * Size;

	// Loop to spawn each block
	for(int32 BlockIndex=0; BlockIndex<NumBlocks; BlockIndex++)
	{
		const float XOffset = (BlockIndex/Size) * BlockSpacing; // Divide by dimension
		const float YOffset = (BlockIndex%Size) * BlockSpacing; // Modulo gives remainder

		// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a block
		blocks[BlockIndex] = GetWorld()->SpawnActor<ATicBlock>(BlockLocation, FRotator(0,0,0));

		// Tell the block about its owner
		if (blocks[BlockIndex] != nullptr)
		{
			blocks[BlockIndex]->OwningGrid = this;
		}
	}
}


void ATicBlockGrid::AddScore()
{
	// Increment score
	Score++;

	/*
	When checking for X's and O's the isX wont work since it will always be set to false which is what
	you were going to use to determine if it was an x or o
	so instead make a string or and int to determine x and o 
	something that can be set to a third state instead of just 2
	since it will have to be deafulted to one or the other

	6-7-8
	3-4-5
	0-1-2

	*/
	//Green = Y; Orange = X;

	//Bottom Row 
	if (Score > 8 && hasWon != true)
	{
		hasWon = true;
		XorO = "Tie";
	}
	else if (blocks[0]->X == 1 && blocks[1]->X == 1 && blocks[2]->X == 1)
	{
		hasWon = true;
		XorO = "X";
	}
	else if (blocks[0]->Y == 1 && blocks[1]->Y == 1 && blocks[2]->Y == 1)
	{
		hasWon = true;
		XorO = "Y";

	}//Middle Row 
	else if (blocks[3]->X == 1 && blocks[4]->X == 1 && blocks[5]->X == 1)
	{
		hasWon = true;
		XorO = "X";
	}
	else if (blocks[3]->Y == 1 && blocks[4]->Y == 1 && blocks[5]->Y == 1)
	{
		hasWon = true;
		XorO = "Y";
	}//Top Row 
	else if (blocks[6]->X == 1 && blocks[7]->X == 1 && blocks[8]->X == 1)
	{
		hasWon = true;
		XorO = "X";
	}
	else if (blocks[6]->Y == 1 && blocks[7]->Y == 1 && blocks[8]->Y == 1)
	{
		hasWon = true;
		XorO = "Y";
	}//Left Column 
	else if (blocks[6]->X == 1 && blocks[3]->X == 1 && blocks[0]->X == 1)
	{
		hasWon = true;
		XorO = "X";
	}
	else if (blocks[6]->Y == 1 && blocks[3]->Y == 1 && blocks[0]->Y == 1)
	{
		hasWon = true;
		XorO = "Y";
	}//Middle Column
	else if (blocks[4]->X == 1 && blocks[7]->X == 1 && blocks[1]->X == 1)
	{
		hasWon = true;
		XorO = "X";
	}
	else if (blocks[4]->Y == 1 && blocks[7]->Y == 1 && blocks[1]->Y == 1)
	{
		hasWon = true;
		XorO = "Y";
	}//Right Column
	else if (blocks[8]->X == 1 && blocks[5]->X == 1 && blocks[2]->X == 1)
	{
		hasWon = true;
		XorO = "X";
	}
	else if (blocks[8]->Y == 1 && blocks[5]->Y == 1 && blocks[2]->Y == 1)
	{
		hasWon = true;
		XorO = "Y";
	}//Diagnol from top left to bottom right
	else if (blocks[6]->X == 1 && blocks[4]->X == 1 && blocks[2]->X == 1)
	{
		hasWon = true;
		XorO = "X";
	}
	else if (blocks[6]->Y == 1 && blocks[4]->Y == 1 && blocks[2]->Y == 1)
	{
		hasWon = true;
		XorO = "Y";
	}//diagnol from top righjt to bottom left
	else if (blocks[8]->X == 1 && blocks[4]->X == 1 && blocks[0]->X == 1)
	{
		hasWon = true;
		XorO = "X";
	}
	else if (blocks[8]->Y == 1 && blocks[4]->Y == 1 && blocks[0]->Y == 1)
	{
		hasWon = true;
		XorO = "Y";
	}
	else	// Update text
	{
		if(isX)
			ScoreText->SetText(FString("Green Turn"));
		else
			ScoreText->SetText(FString("Orange Turn"));
	}

	
}

#undef LOCTEXT_NAMESPACE
