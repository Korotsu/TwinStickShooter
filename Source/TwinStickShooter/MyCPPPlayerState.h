// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "GameFramework/GameState.h"
#include "MyCPPPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTER_API AMyCPPPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	UPROPERTY(replicated, Category = Variables, EditAnywhere, BlueprintReadWrite)
	int myPlayerID;

	UPROPERTY(replicated, ReplicatedUsing = OnRep_UserName, Category = Variables, EditAnywhere, BlueprintReadWrite)
	FString userName;

	UPROPERTY(replicated, ReplicatedUsing = OnRep_shipColor, Category = Variables, EditAnywhere, BlueprintReadWrite)
	FLinearColor shipColor;

	UFUNCTION(BlueprintImplementableEvent)
		void OnRep_UserName();

	UFUNCTION(BlueprintImplementableEvent)
		void OnRep_shipColor();

	AMyCPPPlayerState();
	
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >&
		OutLifetimeProps) const override;

	virtual void CopyProperties(class APlayerState* PlayerState) override;

	virtual void BeginPlay() override;
};
