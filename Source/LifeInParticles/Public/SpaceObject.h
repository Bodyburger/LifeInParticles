// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceObject.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UNiagaraSystem;

UCLASS()
class LIFEINPARTICLES_API ASpaceObject : public AActor
{
	GENERATED_BODY()

public:
	ASpaceObject();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(
			class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "Scaling")
		float MaxScale;

	UPROPERTY(EditAnywhere, Category = "Scaling")
		float AgingRate;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere)
		UNiagaraSystem* DestroyEffect;

	float CurrentScale;

};
