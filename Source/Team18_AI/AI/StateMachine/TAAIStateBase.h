#pragma once

#include "CoreMinimal.h"
#include "TAAIStateBase.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TEAM18_AI_API UTAAIStateBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void Setup();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_Setup();

	virtual FName TickActive(float DeltaTime);
	UFUNCTION(BlueprintImplementableEvent)
    void BP_TickActive(float DeltaTime);

	virtual void OnActivated();
	UFUNCTION(BlueprintImplementableEvent)
    void BP_OnActivated();

	virtual void OnDeactivated();
	UFUNCTION(BlueprintImplementableEvent)
    void BP_OnDeactivated();

	virtual void OnRemoved();
	UFUNCTION(BlueprintImplementableEvent)
    void BP_OnRemoved();

	UFUNCTION(BlueprintCallable)
	void ChangeState(FName NewPendingStateName);

	UPROPERTY(EditAnywhere)
	FName StateName;

	UFUNCTION(BlueprintPure)
	AActor* GetOwner() const;

	UPROPERTY(Transient)
	AActor* Owner = nullptr;

private:
	FName PendingStateName;	
};
