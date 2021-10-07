// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "TwinStickShooterGameMode.h"
#include "TwinStickShooter.h"
#include "TwinStickShooterPawn.h"
#include "GameFrameWork/PlayerStart.h"

ATwinStickShooterGameMode::ATwinStickShooterGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ATwinStickShooterPawn::StaticClass();
}

AActor * ATwinStickShooterGameMode::ChoosePlayerStart_Implementation(AController * Player)
{
	TArray<AActor*> FoundPlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundPlayerStarts);

	for (auto& actor : FoundPlayerStarts)
	{
		APlayerStart* playerStart = Cast<APlayerStart>(actor);
		if (playerStart->PlayerStartTag != FName("Taken"))
		{
			playerStart->PlayerStartTag = FName("Taken");
			return playerStart;
		}
	}

	return nullptr;
}
