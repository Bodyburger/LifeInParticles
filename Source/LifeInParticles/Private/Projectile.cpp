// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h" 
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h" 
#include "Kismet/GameplayStatics.h" 
#include "GameFramework/ProjectileMovementComponent.h" 

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComp->InitSphereRadius(100.f);
	SphereComp->SetCollisionProfileName(TEXT("Trigger"));
	SphereComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	RootComponent = SphereComp;
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileComponent->InitialSpeed = 800.f;
	ProjectileComponent->MaxSpeed = 800.f;
	ProjectileComponent->ProjectileGravityScale = 0.f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (ProjectileEffect)
	{
		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
			ProjectileEffect,
			GetRootComponent(),
			NAME_None,
			FVector(0.f),
			FRotator(0.f),
			EAttachLocation::Type::KeepRelativeOffset,
			true);
	}

}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnOverlapBegin(
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