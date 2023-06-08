
#include "BigBangManager.h"
#include "SpaceObject.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ABigBangManager::ABigBangManager()
{
    PrimaryActorTick.bCanEverTick = false;
    SpawnInterval = 1.0f;
    SpawnRadius = 100.0f;
}

void ABigBangManager::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(
        SpawnTimerHandle,
        this,
        &ABigBangManager::SpawnGameObject,
        SpawnInterval,
        true);
}

void ABigBangManager::SpawnGameObject()
{
    FVector SpawnLocation = GetActorLocation();
    FRotator SpawnRotation = GetActorRotation();
    FVector SpawnDirection = SpawnRotation.Vector();

    FVector Offset = FMath::VRand() * SpawnRadius;
    FVector SpawnPosition = SpawnLocation + Offset;

    ASpaceObject* SpawnedSpaceObject = GetWorld()->SpawnActor<ASpaceObject>(
        SpaceObject,
        SpawnPosition,
        SpawnRotation);

    if (SpawnedSpaceObject)
    {
        SpawnedSpaceObject->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
    }
}
