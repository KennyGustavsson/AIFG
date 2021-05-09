#pragma once

#include "Team18_AI/AI/StateMachine/TAAIStateBase.h"
#include "TAAIPatrolState.generated.h"

class UNavigationQueryFilter;
class USplineComponent;
class ATAEnemy;

UCLASS(Blueprintable, BlueprintType)
class TEAM18_AI_API UTAAIPatrolState : public UTAAIStateBase
{
	GENERATED_BODY()
	
public:
	virtual void Setup() override;
	virtual FName TickActive(float DeltaTime) override;
	virtual void OnActivated() override;
	virtual void OnDeactivated() override;
	virtual void OnRemoved() override;

private:
	UPROPERTY(Transient)
	ATAEnemy* ThisEnemy;
	
	UPROPERTY(Transient)
	USplineComponent* Spline;

	UPROPERTY(EditAnywhere)
	float DistanceOffsetAlongSpline = 50.0f;
	
	float DistanceAlongSpline = 0;
};
