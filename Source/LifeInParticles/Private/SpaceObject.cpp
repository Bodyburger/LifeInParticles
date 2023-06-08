// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceObject.h"
#include "Components/SphereComponent.h" 
#include "Components/StaticMeshComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h" 

ASpaceObject::ASpaceObject()
{
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComp->InitSphereRadius(100.f);
	SphereComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	RootComponent = SphereComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	BaseMesh->SetupAttachment(SphereComp);

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASpaceObject::OnOverlapBegin);
}

void ASpaceObject::BeginPlay()
{
	Super::BeginPlay();

}

void ASpaceObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentScale += AgingRate * DeltaTime;
	SetActorScale3D(FVector(CurrentScale, CurrentScale, CurrentScale));

	if (CurrentScale >= MaxScale)
	{
		Destroy();
	}
}

void ASpaceObject::OnOverlapBegin(
	class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (DestroyEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			DestroyEffect,
			OtherActor->GetActorLocation(),
			FRotator::ZeroRotator,
			FVector(1, 1, 1),
			true,
			true,
			ENCPoolMethod::AutoRelease);
	}
	Destroy();
}

