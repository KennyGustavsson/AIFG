#include "SoundEvent.h"
#include "Kismet/GameplayStatics.h"
#include "Team18_AI/Team18_AIGameMode.h"

void USoundEvent::SpawnSoundEvent(FSoundEventData SoundEvent)
{
	auto* GameMode = Cast<ATeam18_AIGameMode>(UGameplayStatics::GetGameMode(SoundEvent.Instigator));
	GameMode->AddNoise(SoundEvent);
}
