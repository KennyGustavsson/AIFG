#pragma once

#include "Team18_AI/AI/StateMachine/TAAIStateBase.h"
#include "TAAICombatState.generated.h"

UCLASS(Blueprintable, BlueprintType)
class TEAM18_AI_API UTAAICombatState : public UTAAIStateBase
{
	GENERATED_BODY()

public:
	virtual void Setup() override;
	virtual FName TickActive(float DeltaTime) override;
	virtual void OnActivated() override;
	virtual void OnDeactivated() override;
	virtual void OnRemoved() override;
};
