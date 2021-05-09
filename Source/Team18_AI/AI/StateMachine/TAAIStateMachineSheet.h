#pragma once

#include "Engine/DataAsset.h"
#include "TAAIStateMachineSheet.generated.h"

class UTAAIStateBase;

UCLASS()
class TEAM18_AI_API UTAAIStateMachineSheet : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category=AI)
	TArray<TSubclassOf<UTAAIStateBase>> AIStates;

	UPROPERTY(EditDefaultsOnly, Category=AI)
	TSubclassOf<UTAAIStateBase> StartingState;
};
