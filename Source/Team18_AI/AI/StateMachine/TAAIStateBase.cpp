#include "TAAIStateBase.h"

void UTAAIStateBase::Setup()
{
	BP_Setup();
}

FName UTAAIStateBase::TickActive(float DeltaTime)
{
	BP_TickActive(DeltaTime);

	return PendingStateName;
}

void UTAAIStateBase::OnActivated()
{
	BP_OnActivated();
}

void UTAAIStateBase::OnDeactivated()
{
	BP_OnDeactivated();
}

void UTAAIStateBase::OnRemoved()
{
	PendingStateName = NAME_None;
	BP_OnRemoved();
}

void UTAAIStateBase::ChangeState(FName NewPendingStateName)
{
	PendingStateName = NewPendingStateName;
}

AActor* UTAAIStateBase::GetOwner() const
{
	return Owner;
}
