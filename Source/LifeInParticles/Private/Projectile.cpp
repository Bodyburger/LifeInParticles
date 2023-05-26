// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h" 

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (ProjectileEffect)
	{
		// This spawns the chosen effect on the owning WeaponMuzzle SceneComponent
		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
			ProjectileEffect,
			 GetRootComponent(),
			  NAME_None,
			   FVector(0.f),
			    FRotator(0.f),
				 EAttachLocation::Type::KeepRelativeOffset,
				  true);
		// Parameters can be set like this (see documentation for further info) - 
		// the names and type must match the user exposed parameter in the Niagara System
		NiagaraComp->SetNiagaraVariableFloat(FString("StrengthCoef"), 1.f);
	}

}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
