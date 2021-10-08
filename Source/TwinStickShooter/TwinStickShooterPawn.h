// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/Character.h"
#include "Engine/NetSerialization.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/GameState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerState.h"

/*USTRUCT()
struct FSavedMove
{
	GENERATED_BODY()

	float timeStamp = 0;
	float deltaTime = 0;
	FVector movement = FVector::ZeroVector;

	FSavedMove(float& _TimeStamp, float& _DeltaTime, FVector& _Movement) : timeStamp(_TimeStamp), deltaTime(_DeltaTime), movement(_Movement)
	{}

	FSavedMove() = default;
};*/

#include "TwinStickShooterPawn.generated.h"

UCLASS(Blueprintable)
class ATwinStickShooterPawn : public APawn
{
	GENERATED_BODY()

	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;

	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:
	ATwinStickShooterPawn();

	/** Offset from the ships location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite )
	FVector GunOffset;
	
	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float FireRate;

	/* The speed our ship moves around the level */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	int MaxHealthPoints = 10;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float ReviveDelay = 2.0f;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float maxDistanceErrorOffset = 1.0f;

	/** Sound to play each time we fire */
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* FireSound;

	// Begin Actor Interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End Actor Interface

	/* Handler for the fire timer expiry */
	void ShotTimerExpired();

	UFUNCTION(NetMulticast, unreliable)
		void OnScoreUpdateMultiCast(class APlayerState* ps, float score);

	void OnScoreUpdateMultiCast_Implementation(class APlayerState* ps, float score);

	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerState")
		void OnScoreUpdate(class APlayerState* ps, float score);

	// Static names for axis bindings
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;

private:
	/* Flag to control firing  */
	uint32 bCanFire : 1;

	/* Flag to set death state */
	uint32 bIsAlive : 1;

	/* Flag to set the updatePosition state */
	uint32 bUpdatePosition : 1;

	//UCharacterMovementComponent* cMoveComp;
	
	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

	FTimerHandle TimerHandle_Revive;

	UPROPERTY()
	float ForwardValue;
	UPROPERTY()
	float RightValue;

	UPROPERTY()
	FVector MoveDirection;

	//TArray<FSavedMove> savedMoves;

	/*UPROPERTY(ReplicatedUsing = OnRep_ReplicatedMovement)
	FSavedMove replicatedMove;*/

	int CurrentHealthPoints;

	/* Fire a shot in the specified direction */
	void FireShot(FVector FireDirection);

	UFUNCTION(server, unreliable, WithValidation)
		void ServerFireShot(const FVector& FireDirection);

	void ServerFireShot_Implementation(const FVector& FireDirection);
	bool ServerFireShot_Validate(const FVector& FireDirection);

	void ProcessFireShot(const FVector& FireDirection);

	/* Compute Pawn movement */	
	void ComputeMove(float DeltaSeconds);

	UFUNCTION(server, unreliable, WithValidation)
	void ServerMove(const FVector& Movement);

	void ServerMove_Implementation(const FVector& Movement);
	bool ServerMove_Validate(const FVector& Movement);

	UFUNCTION(NetMulticast, unreliable)
		void PerformReceivedMove(const FVector& Movement);

	void PerformReceivedMove_Implementation(const FVector& Movement);

	void ProcessMovement(const FVector& Movement);

	/* Revive Pawn */
	void Revive();

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	/*void ClientUpdatePositionAfterServerUpdate();

	void ReplicateMoveToServer(float DeltaSeconds);

	void MoveAutonomous(const FSavedMove& movement);

	FSavedMove& CreateMove(float deltaTime);

	void PerformMovement(float DeltaTime, FVector movement);

	UFUNCTION(unreliable, server, WithValidation)
		void ServerMove(float timeStamp, float deltaTime, FVector_NetQuantize10 movement, FVector_NetQuantize10 clientPos);

	void ServerMove_Implementation(float timeStamp, float deltaTime, FVector_NetQuantize10 movement, FVector_NetQuantize10 clientPos);
	bool ServerMove_Validate();
	
	void CallServerMove(const FSavedMove& move);

	void ServerMoveHandleClientError(FVector clientPos, FVector serverPos);*/

	/*UFUNCTION()
	void OnRep_ReplicatedMove();*/

	/*virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >&
		OutLifetimeProps) const override
	{
		Super::GetLifetimeReplicatedProps(OutLifetimeProps);
		DOREPLIFETIME(ATwinStickShooterPawn, ShipMeshComponent);
		DOREPLIFETIME(ATwinStickShooterPawn, CameraComponent);
		DOREPLIFETIME(ATwinStickShooterPawn, CameraBoom);
	}*/

public:
	/** Returns ShipMeshComponent subobject **/
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
	/** Returns CameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};