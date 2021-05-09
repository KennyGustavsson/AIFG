#include "TAListeneningComponent.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Team18_AI/Team18_AIGameMode.h"
#include "Team18_AI/BlueprintFunctions/SoundEvent.h"

UTAListeneningComponent::UTAListeneningComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTAListeneningComponent::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ATeam18_AIGameMode>(UGameplayStatics::GetGameMode(this));
}

void UTAListeneningComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<FSoundEventData*> ListOfTargets;
	GameMode->GetHeardNoise(ListOfTargets, GetOwner()->GetActorLocation(), HearingMinDistance);

	for(FSoundEventData* Target : ListOfTargets)
	{
		if(!Target->ListenersHeard.Contains(this))
		{
			Target->ListenersHeard.Add(this);
			FSoundEventResult Results;
			Results.Location = Target->Location;
			OnNoiseHeard.Broadcast(Results);
		}
	}

	if(bDebugHearingRange)
	{
		DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(), HearingMinDistance, 12, FColor::Red);
	}
}

