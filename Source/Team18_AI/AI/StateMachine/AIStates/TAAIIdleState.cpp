#include "TAAIIdleState.h"

void UTAAIIdleState::Setup()
{
	Super::Setup();
}

FName UTAAIIdleState::TickActive(float DeltaTime)
{
	Super::TickActive(DeltaTime);

	return StateName;
}

void UTAAIIdleState::OnActivated()
{
	Super::OnActivated();
}

void UTAAIIdleState::OnDeactivated()
{
	Super::OnDeactivated();
}

void UTAAIIdleState::OnRemoved()
{
	Super::OnRemoved();
}
