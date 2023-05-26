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
#include "GameFramework/MovementComponent.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(GetRootComponent());
	ViewCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	ViewCamera->SetOrthoWidth(7500.f);
	ViewCamera->bUsePawnControlRotation = false;

	ShipSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("ShipSphereComponent"));
	ShipSphereComp->SetupAttachment(GetRootComponent());

	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMeshComponent"));
	ShipMesh->SetupAttachment(GetRootComponent());

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(GetRootComponent());

	MovementComponent = CreateDefaultSubobject<UMovementComponent>(TEXT("MovementComponent"));

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
	}
}

void APlayerPawn::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y, true);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X, true);
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

}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
