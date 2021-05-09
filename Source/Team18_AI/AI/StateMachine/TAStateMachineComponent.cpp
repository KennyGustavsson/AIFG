#include "TAStateMachineComponent.h"
#include "TAAIStateBase.h"
#include "TAAIStateMachineSheet.h"

UTAStateMachineComponent::UTAStateMachineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UTAStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();

	LoadSheet();
	
	if(CurrentState)
	{
		CurrentState->OnActivated();
		CurrentStateName = CurrentState->StateName;
	}
}

void UTAStateMachineComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnloadSheet();

	Super::EndPlay(EndPlayReason);
}

void UTAStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	 if(CurrentState == nullptr)
	 {
	 	return;
	 }
	
	const FName NewStateName = CurrentState->TickActive(DeltaTime);

	if(NewStateName != NAME_None)
	{
		UTAAIStateBase* NewState = GetStateFromName(NewStateName);

		if(!ensureMsgf(NewState != nullptr, TEXT("Unable to change AI state, state: %s not found"), *NewStateName.ToString()))
		{
			return;
		}

		CurrentState->OnDeactivated();
		NewState->OnActivated();
		CurrentState = NewState;
		CurrentStateName = CurrentState->StateName;
	}
}

void UTAStateMachineComponent::SetSheet(UTAAIStateMachineSheet* NewSheet)
{
	AIStateMachineSheet = NewSheet;
	LoadSheet();
}

void UTAStateMachineComponent::ChangeStateFromName(FName StateName)
{
	UTAAIStateBase* NewState = GetStateFromName(StateName);

	if(!NewState)
		return;

	CurrentState->OnDeactivated();
	NewState->OnActivated();
	CurrentState = NewState;
	CurrentStateName = CurrentState->StateName;
}

void UTAStateMachineComponent::ChangeStateFromClass(TSubclassOf<UTAAIStateBase> ClassType)
{
	UTAAIStateBase* NewState = GetStateFromClass(ClassType);

	if(!NewState)
		return;

	CurrentState->OnDeactivated();
	NewState->OnActivated();
	CurrentState = NewState;
	CurrentStateName = CurrentState->StateName;
}

void UTAStateMachineComponent::LoadSheet()
{
	if(!ensureMsgf(AIStateMachineSheet != nullptr, TEXT("Invalid StateMachineSheet")))
	{
		return;
	}

	UnloadSheet();

	for(auto StateClass : AIStateMachineSheet->AIStates)
	{
		UTAAIStateBase* AIState = NewObject<UTAAIStateBase>(GetOwner(), StateClass);
		if(!ensure(AIState != nullptr))
		{
			continue;
		}

		AIState->Owner = GetOwner();
		AIState->Setup();
		AIStates.Add(AIState);
	}

	CurrentState = GetStateFromClass(AIStateMachineSheet->StartingState);
	CurrentStateName = CurrentState->StateName;
	ensureMsgf(CurrentState != nullptr, TEXT("Unable to find starting state"));
}

void UTAStateMachineComponent::UnloadSheet()
{
	for(auto State : AIStates)
	{
		if(!State)
		{
			continue;
		}

		State->OnRemoved();
	}

	AIStates.Empty();
}

UTAAIStateBase* UTAStateMachineComponent::GetStateFromClass(TSubclassOf<UTAAIStateBase> ClassType) const
{
	for(auto State : AIStates)
	{
		if(State->GetClass() == ClassType)
		{
			return State;
		}
	}

	return nullptr;
}

UTAAIStateBase* UTAStateMachineComponent::GetStateFromName(FName StateName) const
{
	for(auto State : AIStates)
	{
		if(!State)
		{
			continue;
		}

		if(State->StateName == StateName)
		{
			return State;
		}
	}

	return nullptr;
}
