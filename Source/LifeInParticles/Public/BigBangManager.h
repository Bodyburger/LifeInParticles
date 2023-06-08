#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BigBangmanager.generated.h"

class ASpaceObject;

UCLASS()
class LIFEINPARTICLES_API ABigBangManager : public AActor
{
    GENERATED_BODY()

public:
    ABigBangManager();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BigBangManager")
    TSubclassOf<ASpaceObject> SpaceObject;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BigBangManager")
    float SpawnInterval;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BigBangManager")
    float SpawnRadius;

protected:
    virtual void BeginPlay() override;

private:
    void SpawnGameObject();

    FTimerHandle SpawnTimerHandle;
};