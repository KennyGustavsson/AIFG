#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TAAIEnemyCover.generated.h"

class UBoxComponent;

UCLASS()
class TEAM18_AI_API ATAAIEnemyCover : public AActor
{
	GENERATED_BODY()

public:
	ATAAIEnemyCover();
	virtual void BeginPlay() override;

	UPROPERTY()
	UBoxComponent* BoxComponent;
};
