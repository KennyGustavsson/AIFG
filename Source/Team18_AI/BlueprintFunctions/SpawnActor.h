#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SpawnActor.generated.h"

UCLASS()
class TEAM18_AI_API USpawnActor : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, meta=(DistplayName = "Spawn Actor", CompactTitle = "SpawnActor", Category = "Custom"))
	static void SpawnActor(AActor* Spawner, UClass* Class, FVector const Location, FRotator const Rotation);
};
