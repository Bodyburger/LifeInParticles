// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h" 
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Sound/SoundBase.h"
#include "GameFramework/PawnMovementComponent.h" 
#include "Kismet/GameplayStatics.h" 
#include "Projectile.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	ViewCamera->SetOrthoWidth(7500.f);
	ViewCamera->bUsePawnControlRotation = false;

	ShipSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("ShipSphereComponent"));
	RootComponent = ShipSphereComp;

	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMeshComponent"));
	ShipMesh->SetupAttachment(ShipSphereComp);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(ShipSphereComp);

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent>(TEXT("MovementComponent"));

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerContext, 0);
		}
	}
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &APlayerPawn::Move);
		EnhancedInputComponent->BindAction(PauseGameAction, ETriggerEvent::Triggered, this, &APlayerPawn::PauseGame);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &APlayerPawn::Shoot);
	}
}

void APlayerPawn::Move(const FInputActionValue& Value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	const FVector2D MovementVector = Value.Get<FVector2D>();

	DeltaLocation.X = MovementVector.X * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed;
	AddActorLocalOffset(DeltaLocation, true);

	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = MovementVector.Y * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate;
	AddActorLocalRotation(DeltaRotation, true);
}

void APlayerPawn::PauseGame(const FInputActionValue& Value)
{
	if (PlayerController != nullptr)
	{
		PlayerController->SetPause(!bIsPaused);
		bIsPaused = !bIsPaused;
	}
}
void APlayerPawn::Shoot(const FInputActionValue& Value)
{
	FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
	FActorSpawnParameters SpawnInfo;

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnInfo);
	if (Projectile)
	{
		Projectile->SetOwner(this);
	}
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
