#include "TAAIHealthComponent.h"

UTAAIHealthComponent::UTAAIHealthComponent()
{
}

void UTAAIHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void UTAAIHealthComponent::Damage(int Damage, AActor* DamageDealer)
{
	if(CurrentHealth == 0 || bIsDead)
		return;

	if(CurrentHealth - Damage <= 0)
	{
		CurrentHealth = 0;
		bIsDead = true;
		FOnHealthChangeEventData HealthChangeData;
		HealthChangeData.CurrentHealth = CurrentHealth;
		HealthChangeData.Actor = DamageDealer;
		OnHealthChange.Broadcast(HealthChangeData);
		
		OnDeathEvent.Broadcast();
		return;
	}
	
	CurrentHealth -= Damage;
	FOnHealthChangeEventData HealthChangeData;
	HealthChangeData.CurrentHealth = CurrentHealth;
	HealthChangeData.Actor = DamageDealer;
	OnHealthChange.Broadcast(HealthChangeData);
}

void UTAAIHealthComponent::Heal(int Heal)
{
	if(CurrentHealth == MaxHealth || bIsDead)
		return;

	if(CurrentHealth + Heal >= MaxHealth)
	{
		CurrentHealth = MaxHealth;
		FOnHealthChangeEventData HealthChangeData;
		HealthChangeData.CurrentHealth = CurrentHealth;
		OnHealthChange.Broadcast(HealthChangeData);
		
		return;
	}
	
	CurrentHealth += Heal;
	FOnHealthChangeEventData HealthChangeData;
	HealthChangeData.CurrentHealth = CurrentHealth;
	OnHealthChange.Broadcast(HealthChangeData);
}

int UTAAIHealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}
