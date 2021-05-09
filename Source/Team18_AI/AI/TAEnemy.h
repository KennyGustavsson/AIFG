#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TAEnemy.generated.h"

class UCapsuleComponent;
class UTANavMovementComponent;
class USplineComponent;

USTRUCT(BlueprintType)
struct FTAMoveData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	FVector WantedDestination;
};

UCLASS()
class TEAM18_AI_API ATAEnemy : public APawn
{
	GENERATED_BODY()

public:
	ATAEnemy();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleDefaultsOnly, Category=Collision)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category=Movement)
	UTANavMovementComponent* NavMovementComponent;

	virtual float GetDefaultHalfHeight() const override;
	UCapsuleComponent* GetCapsule() const {return Capsule;}

	UPROPERTY(Transient)
	FVector LastPosition = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly)
	float VelocityMagnitude = 0;

	UPROPERTY(EditAnywhere)
	AActor* PatrolSplineActor;

	UFUNCTION(BlueprintImplementableEvent)
	void OnWantedMovement(FTAMoveData MoveData);

	UPROPERTY(BlueprintReadOnly)
	float RotationDeltaMagnitude = 0.0f;

	UPROPERTY(Transient)
	FVector LastRotation = FVector::ZeroVector;
};
