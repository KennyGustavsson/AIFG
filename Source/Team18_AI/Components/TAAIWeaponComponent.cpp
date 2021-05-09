#include "TAAIWeaponComponent.h"
#include "Team18_AI/Weapon/TAAIWeaponBase.h"
#include "Camera/CameraComponent.h"

UTAAIWeaponComponent::UTAAIWeaponComponent()
{
}

void UTAAIWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	LoadInWeapons();
}

void UTAAIWeaponComponent::FireWeapon()
{
	if(Weapons.Num() == 0)
		return;

	WeaponBases[WeaponIndex]->Fire(GetOwner(), GetOwner()->GetActorLocation(), GetOwner()->GetActorForwardVector());
}

void UTAAIWeaponComponent::FireWeaponFromCameraComponent(UCameraComponent* Component)
{
	if(Weapons.Num() == 0)
		return;

	if(WeaponBases[WeaponIndex])
		WeaponBases[WeaponIndex]->Fire(GetOwner(), GetOwner()->GetActorLocation(), GetOwner()->GetActorForwardVector(), Component);
}

void UTAAIWeaponComponent::FireWeaponAtLocation(FVector location)
{
	if(Weapons.Num() == 0)
		return;
	
	if(WeaponBases[WeaponIndex])
		WeaponBases[WeaponIndex]->Fire(GetOwner(), GetOwner()->GetActorLocation(), location, nullptr, true);
}

void UTAAIWeaponComponent::ChangeWeaponIndex(int Index)
{
	WeaponIndex = Index % Weapons.Num(); 
}

void UTAAIWeaponComponent::LoadInWeapons()
{
	WeaponBases.Empty();
	
	for(auto StateClass : Weapons)
	{
		UTAAIWeaponBase* Weapon = NewObject<UTAAIWeaponBase>(GetOwner(), StateClass);
		if(!ensure(Weapon != nullptr))
		{
			continue;
		}

		WeaponBases.Add(Weapon);
	}
}
