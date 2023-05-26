// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BigBangManager.generated.h"

class UNiagaraComponent;

UCLASS()
class LIFEINPARTICLES_API ABigBangManager : public AActor
{
	GENERATED_BODY()

public:
	ABigBangManager();
	virtual void Tick(float DeltaTime) override;

	// UFUNCTION()
	// void SpawnRocks();

protected:
	virtual void BeginPlay() override;

private:
	// TODO: create ARock script to spawn
};
