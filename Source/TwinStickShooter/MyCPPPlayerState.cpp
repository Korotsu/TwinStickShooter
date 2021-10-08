// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "GameFramework/GameState.h"
#include "MyCPPPlayerState.h"

AMyCPPPlayerState::AMyCPPPlayerState()
{
	userName = "";
	myPlayerID = 0;

	SetReplicates(true);
}

void AMyCPPPlayerState::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >&
	OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMyCPPPlayerState, myPlayerID);
	DOREPLIFETIME(AMyCPPPlayerState, userName);
}

void AMyCPPPlayerState::CopyProperties(class APlayerState* PlayerState)
{
	APlayerState::CopyProperties(PlayerState);

	AMyCPPPlayerState* MyPlayerState = Cast<AMyCPPPlayerState>(PlayerState);

    if (MyPlayerState)
    {
        MyPlayerState->userName = userName;
		MyPlayerState->myPlayerID = myPlayerID;
    }

}

void AMyCPPPlayerState::BeginPlay()
{
	myPlayerID = GetWorld()->GetGameState()->PlayerArray.Num();
}