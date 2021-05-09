#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TAAIWeaponComponent.generated.h"

class UCameraComponent;

class UTAAIWeaponBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TEAM18_AI_API UTAAIWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTAAIWeaponComponent();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void FireWeapon();

	UFUNCTION(BlueprintCallable)
	void FireWeaponFromCameraComponent(UCameraComponent* Component);

	UFUNCTION(BlueprintCallable)
	void FireWeaponAtLocation(FVector location);

	UFUNCTION(BlueprintCallable)
	void ChangeWeaponIndex(int Index);

	UFUNCTION(BlueprintCallable)
	void LoadInWeapons();

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UTAAIWeaponBase>> Weapons;

	UPROPERTY(Transient)
	TArray<UTAAIWeaponBase*> WeaponBases;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WeaponIndex = 0;

	UPROPERTY(EditAnywhere)
	FVector ShootOffset = FVector::ZeroVector;
};
