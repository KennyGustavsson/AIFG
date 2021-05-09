#include "TAAIHitScan.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "Team18_AI/Components/TAAIHealthComponent.h"

void UTAAIHitScan::Fire(AActor* ActorOwner, FVector Origin, FVector Direction, UCameraComponent* Component, bool DirectionIsEndLocation)
{
	FHitResult Hit;

	TArray<AActor*> Ignores;
	Ignores.Add(ActorOwner);
	
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("Vision_Trace")),
		true);
	TraceParams.AddIgnoredActors(Ignores);
	TraceParams.bReturnPhysicalMaterial = false;

	FVector Start;
	FVector End;

	if(DirectionIsEndLocation)
	{
		Start = Origin;
		End = Direction;
	}
	else if(Component != nullptr)
	{
		Start = Component->GetComponentLocation();
		End = Component->GetComponentLocation() + (Component->GetComponentRotation().Vector() * ShootDistance);
	}
	else
	{
		Start = Origin;
		End = Direction * ShootDistance;
	}

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Pawn, TraceParams);	
	
	if(bDrawDebug)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Purple, false, 1, 0, 2);
		if(Hit.bBlockingHit)
		{
			DrawDebugBox(GetWorld(), Hit.ImpactPoint, FVector(5), FColor::Blue, false, 1, 0, 2);
		}
	}

	if(Hit.bBlockingHit)
	{
		auto HealthComponent = Hit.Actor->FindComponentByClass<UTAAIHealthComponent>();

		if(HealthComponent)
		{
			HealthComponent->Damage(Damage, ActorOwner);

			if(bDrawDebug)
				UE_LOG(LogTemp, Log, TEXT("Hit Enemy, Health is : %f"), (float)HealthComponent->GetCurrentHealth());
		}
	}
}
