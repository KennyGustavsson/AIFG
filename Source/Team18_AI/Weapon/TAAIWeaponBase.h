#pragma once

#include "CoreMinimal.h"
#include "TAAIWeaponBase.generated.h"

class UCameraComponent;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TEAM18_AI_API UTAAIWeaponBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void Fire(AActor* ActorOwner, FVector Origin, FVector Direction, UCameraComponent* Component = nullptr, bool DirectionIsEndLocation = false);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_Fire(AActor* ActorOwner, FVector Origin, FVector Direction, UCameraComponent* Component = nullptr, bool DirectionIsEndLocation = false);
};
