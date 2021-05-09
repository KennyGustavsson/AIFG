#include "TAAICoverState.h"
#include "Kismet/GameplayStatics.h"
#include "Team18_AI/Team18_AIGameMode.h"
#include "Team18_AI/AI/TAEnemy.h"

void UTAAICoverState::Setup()
{
	MaxDistanceSq = FMath::Square(MaxDistanceToCover);
	ThisEnemy = Cast<ATAEnemy>(Owner);
}

FName UTAAICoverState::TickActive(float DeltaTime)
{
	return StateName;
}

void UTAAICoverState::OnActivated()
{
	if(!ThisEnemy)
		return;
		
	auto GameMode = Cast<ATeam18_AIGameMode>(UGameplayStatics::GetGameMode(this));
	if(GameMode)
	{
		CoverPosition = GameMode->GetClosestCoverPoint(Owner->GetActorLocation());

		if(CoverPosition == FVector::ZeroVector)
			return;
		
		float DistanceSq = FVector::DistSquared(Owner->GetActorLocation(), CoverPosition);
		if(DistanceSq > MaxDistanceSq)
			return;

		FTAMoveData MoveData;
		MoveData.WantedDestination = CoverPosition;
		ThisEnemy->OnWantedMovement(MoveData);
	
	}
}

void UTAAICoverState::OnDeactivated()
{
	
}

void UTAAICoverState::OnRemoved()
{
	
}
