// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class LIFEINPARTICLES_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* ProjectileEffect;
	
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* DestroyEffect;
};
