#pragma once

#include "TAAIWeaponBase.h"
#include "TAAIHitScan.generated.h"

UCLASS(Blueprintable)
class TEAM18_AI_API UTAAIHitScan : public UTAAIWeaponBase
{
	GENERATED_BODY()

public:
	virtual void Fire(AActor* ActorOwner, FVector Origin, FVector Direction, UCameraComponent* Component = nullptr, bool DirectionIsEndLocation = false) override;

	UPROPERTY(EditAnywhere, Category=Weapon)
	int Damage = 50;

	UPROPERTY(EditAnywhere, Category=Weapon)
	float ShootDistance = 10000.0f;
	
	UPROPERTY(EditAnywhere, Category=Debug)
	bool bDrawDebug = false;

	UPROPERTY(EditAnywhere, Category=Weapon)
	bool bCastFromCamera = false;

};
