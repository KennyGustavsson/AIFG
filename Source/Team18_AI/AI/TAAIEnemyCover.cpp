#include "TAAIEnemyCover.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Team18_AI/Team18_AIGameMode.h"

ATAAIEnemyCover::ATAAIEnemyCover()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = BoxComponent;
}

void ATAAIEnemyCover::BeginPlay()
{
	Super::BeginPlay();

	auto GameMode = Cast<ATeam18_AIGameMode>(UGameplayStatics::GetGameMode(this));
	if(GameMode)
		GameMode->AddCoverPoint(GetActorLocation());
}
