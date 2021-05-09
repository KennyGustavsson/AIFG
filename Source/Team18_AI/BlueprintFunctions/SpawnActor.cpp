#include "SpawnActor.h"

void USpawnActor::SpawnActor(AActor* Spawner, UClass* Class, FVector const Location, FRotator const Rotation)
{
	FTransform trans;
	trans.SetLocation(Location);
	trans.SetRotation(Rotation.Quaternion());
	Spawner->GetWorld()->SpawnActor<AActor>(Class, trans);
}
