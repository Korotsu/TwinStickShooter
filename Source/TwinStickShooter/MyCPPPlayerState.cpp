// Fill out your copyright notice in the Description page of Project Settings.
#include "MyCPPPlayerState.h"

AMyCPPPlayerState::AMyCPPPlayerState()
{
	userName = "";
	myPlayerID = 0;
	shipColor.R = 0;
	shipColor.G = 0;
	shipColor.B = 0;
	shipColor.A = 1;

	SetReplicates(true);
}

void AMyCPPPlayerState::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >&
	OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMyCPPPlayerState, myPlayerID);
	DOREPLIFETIME(AMyCPPPlayerState, userName);
	DOREPLIFETIME(AMyCPPPlayerState, shipColor);
}

void AMyCPPPlayerState::CopyProperties(class APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	AMyCPPPlayerState* MyPlayerState = Cast<AMyCPPPlayerState>(PlayerState);

    if (MyPlayerState)
    {
        MyPlayerState->userName		= userName;
		MyPlayerState->myPlayerID	= myPlayerID;
		MyPlayerState->shipColor	= shipColor;
    }

}

void AMyCPPPlayerState::BeginPlay()
{
	if (myPlayerID == 0)
	{
		myPlayerID = GetWorld()->GetGameState()->PlayerArray.Num();
	}
}