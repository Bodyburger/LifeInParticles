// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PlayerPawn.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class UMovementComponent;
class USphereComponent;
class UNiagaraComponent;
class UStaticMeshComponent;

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

	UPROPERTY()
		USphereComponent* ShipSphereComp;

	UPROPERTY()
		UStaticMeshComponent* ShipMesh;

private:
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* ViewCamera;

	APlayerController* PlayerController;

	bool bIsPaused = false;

};
