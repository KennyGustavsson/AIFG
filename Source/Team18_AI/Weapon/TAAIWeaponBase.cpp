#include "TAAIWeaponBase.h"

void UTAAIWeaponBase::Fire(AActor* ActorOwner, FVector Origin, FVector Direction, UCameraComponent* Component, bool DirectionIsEndLocation)
{
	BP_Fire(ActorOwner, Origin, Direction, Component);
}
