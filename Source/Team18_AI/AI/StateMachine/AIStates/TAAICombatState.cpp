#include "TAAICombatState.h"

void UTAAICombatState::Setup()
{
}

FName UTAAICombatState::TickActive(float DeltaTime)
{
	return StateName;
}

void UTAAICombatState::OnActivated()
{
}

void UTAAICombatState::OnDeactivated()
{
}

void UTAAICombatState::OnRemoved()
{
}
