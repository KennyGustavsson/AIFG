#pragma once

#include "Components/ActorComponent.h"
#include "TAStateMachineComponent.generated.h"

class UTAAIStateBase;
class UTAAIStateMachineSheet;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TEAM18_AI_API UTAStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTAStateMachineComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetSheet(UTAAIStateMachineSheet* NewSheet);

	UFUNCTION(BlueprintCallable)
	void ChangeStateFromName(FName StateName);
	
	UFUNCTION(BlueprintCallable)
	void ChangeStateFromClass(TSubclassOf<UTAAIStateBase> ClassType);

	UPROPERTY(BlueprintReadOnly)
	FName CurrentStateName;
	
private:
	void LoadSheet();
	void UnloadSheet();

	UTAAIStateBase* GetStateFromClass(TSubclassOf<UTAAIStateBase> ClassType) const;
	UTAAIStateBase* GetStateFromName(FName StateName) const;

	UPROPERTY(EditAnywhere)
	UTAAIStateMachineSheet* AIStateMachineSheet = nullptr;

	UPROPERTY(Transient)
	TArray<UTAAIStateBase*> AIStates;

	UPROPERTY(Transient)
	UTAAIStateBase* CurrentState;
};
