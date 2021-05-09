#pragma once

#include "Team18_AI/AI/StateMachine/TAAIStateBase.h"
#include "TAAICoverState.generated.h"

class ATAEnemy;

UCLASS(Blueprintable, BlueprintType)
class TEAM18_AI_API UTAAICoverState : public UTAAIStateBase
{
	GENERATED_BODY()
	
public:
	virtual void Setup() override;
	virtual FName TickActive(float DeltaTime) override;
	virtual void OnActivated() override;
	virtual void OnDeactivated() override;
	virtual void OnRemoved() override;

	UPROPERTY(VisibleAnywhere)
	float MaxDistanceToCover = 10000.0f;

	UPROPERTY(Transient)
	float MaxDistanceSq = 0;

	UPROPERTY(Transient)
	FVector CoverPosition = FVector::ZeroVector;

	UPROPERTY(Transient)
	ATAEnemy* ThisEnemy;
};
