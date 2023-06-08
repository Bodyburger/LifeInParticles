// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PlayerPawn.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USphereComponent;
class UStaticMeshComponent;
class UPawnMovementComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class USoundBase;

class AProjectile;

UCLASS()
class LIFEINPARTICLES_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	/*
	INPUT
	*/
	UPROPERTY(EditAnywhere, Category = Input)
		UInputMappingContext* PlayerContext;

	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* PauseGameAction;

	UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* ShootAction;

	void Move(const FInputActionValue& Value);
	void PauseGame(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);

	/*
	COMPONENTS
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn Components", meta = (AllowPrivateAccess = "true"))
		USphereComponent* ShipSphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ShipMesh;

private:
	UPROPERTY(EditAnywhere)
		UCameraComponent* ViewCamera;

	bool bIsPaused = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* ProjectileSpawnPoint;

	UPROPERTY()
		UPawnMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float Speed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float TurnRate = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
		UNiagaraSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
		USoundBase* DeathSound;

	UPROPERTY()
		APlayerController* PlayerController;

};
