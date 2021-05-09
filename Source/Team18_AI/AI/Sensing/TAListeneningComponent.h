#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TAListeneningComponent.generated.h"

class UTAListeneningComponent;
class ATeam18_AIGameMode;

USTRUCT(BlueprintType)
struct FSoundEventResult
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	FVector Location = FVector::ZeroVector;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTASoundEventDelegate, const FSoundEventResult&, Results);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TEAM18_AI_API UTAListeneningComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTAListeneningComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	float HearingMinDistance = 1000.0f;

	UPROPERTY(EditAnywhere)
	bool bDebugHearingRange = false;

	UPROPERTY(BlueprintAssignable)
	FTASoundEventDelegate OnNoiseHeard;
	
private:
	ATeam18_AIGameMode* GameMode;
};
