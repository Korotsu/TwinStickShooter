// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Net/UnrealNetwork.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTER_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(replicated, Category = Variables, EditAnywhere, BlueprintReadWrite)
		int winPoints;

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >&
		OutLifetimeProps) const override;
};
