#include "TAAIDeathState.h"

void UTAAIDeathState::Setup()
{
}

FName UTAAIDeathState::TickActive(float DeltaTime)
{
	return StateName;
}

void UTAAIDeathState::OnActivated()
{
}

void UTAAIDeathState::OnDeactivated()
{
}

void UTAAIDeathState::OnRemoved()
{
}
