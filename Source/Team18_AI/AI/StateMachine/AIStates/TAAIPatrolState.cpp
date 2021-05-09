#include "TAAIPatrolState.h"
#include "Components/SplineComponent.h"
#include "AIController.h"
#include "Team18_AI/AI/TAEnemy.h"

void UTAAIPatrolState::Setup()
{
	Super::Setup();

	ThisEnemy = Cast<ATAEnemy>(Owner);
	if(!ThisEnemy)
		return;

	if(ThisEnemy->PatrolSplineActor)
		Spline = ThisEnemy->PatrolSplineActor->FindComponentByClass<USplineComponent>();
}

FName UTAAIPatrolState::TickActive(float DeltaTime)
{
	Super::TickActive(DeltaTime);

	if(!Spline || !ThisEnemy)
		return StateName;
	
	float const InputKey = Spline->FindInputKeyClosestToWorldLocation(Owner->GetActorLocation());
	float Distance = Spline->GetDistanceAlongSplineAtSplineInputKey(InputKey);
	Distance += DistanceOffsetAlongSpline;

	if(Spline->IsClosedLoop())
	{
		if(Distance > Spline->GetSplineLength())
			Distance -= Spline->GetSplineLength();
	}
	else
	{
		if(Distance > Spline->GetSplineLength() ||
			Distance <= 0)
			DistanceOffsetAlongSpline *= -1;
	}
	
	FVector const TargetLocation = Spline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	FVector TargetDirection = (TargetLocation - Owner->GetActorLocation().GetSafeNormal());

	FTAMoveData MoveData;
	MoveData.WantedDestination = TargetLocation;
	ThisEnemy->OnWantedMovement(MoveData);
	
	return StateName;
}

void UTAAIPatrolState::OnActivated()
{
	Super::OnActivated();
}

void UTAAIPatrolState::OnDeactivated()
{
	Super::OnDeactivated();
}

void UTAAIPatrolState::OnRemoved()
{
	Super::OnRemoved();
}
