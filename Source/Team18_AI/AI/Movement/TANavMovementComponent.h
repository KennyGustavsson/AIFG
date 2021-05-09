#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "TANavMovementComponent.generated.h"

UCLASS()
class TEAM18_AI_API UTANavMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	UTANavMovementComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	virtual void StopActiveMovement() override;
	
	virtual bool CanStartPathFollowing() const override;
	virtual bool CanStopPathFollowing() const override;

	virtual float GetPathFollowingBrakingDistance(float MaxSpeed) const override;
	bool FindNavFloor(const FVector& TestLocation, FNavLocation& NavFloorLocation) const;
	
	const INavigationDataInterface* GetNavData() const;

	UFUNCTION(BlueprintPure)
	bool IsMoving() const;

	UPROPERTY(EditAnywhere, Category=Movement, BlueprintReadWrite)
	float MovementSpeed = 400.0f;
	
	UPROPERTY(EditAnywhere)
	float FloorOffset = 0;

	bool bHasRequestedVelocity;
	FVector RequestedVelocity = FVector::ZeroVector;
};
