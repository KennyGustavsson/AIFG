#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TAAIHealthComponent.generated.h"

USTRUCT(BlueprintType)
struct FOnHealthChangeEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	int CurrentHealth = 0;
	AActor* Actor = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTAOnHealthChange, FOnHealthChangeEventData, CurrentHealthData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTAOnDeathEvent);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TEAM18_AI_API UTAAIHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTAAIHealthComponent();
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void Damage(int Damage, AActor* DamageDealer);

	UFUNCTION(BlueprintCallable)
	void Heal(int Heal);

	UPROPERTY(EditDefaultsOnly)
	int MaxHealth = 100;

	UPROPERTY(BlueprintAssignable)
	FTAOnHealthChange OnHealthChange;
	
	UPROPERTY(BlueprintAssignable)
	FTAOnDeathEvent OnDeathEvent;

	UFUNCTION(BlueprintCallable)
	int GetCurrentHealth();

private:
	bool bIsDead = false;
	int CurrentHealth = 0;
};
