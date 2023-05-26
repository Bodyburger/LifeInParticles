// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LifeInParticlesGameMode.generated.h"



UCLASS()
class LIFEINPARTICLES_API ALifeInParticlesGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void SetWidgetVisibility();

private:
	class APlayerPawn* PlayerPawn;
	
	float gameTimer = 60.f;
};
