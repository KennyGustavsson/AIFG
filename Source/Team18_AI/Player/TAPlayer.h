#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TAPlayer.generated.h"

class UCameraComponent;
class UCapsuleComponent;

UCLASS()
class TEAM18_AI_API ATAPlayer : public APawn
{
	GENERATED_BODY()

public:
	ATAPlayer();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* MyCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* MyCapsule;

	//Input Reactions
	void MoveRight(float Value);
	void MoveForward(float Value);
	
	void LookRight(float Value);
	void LookUp(float Value);

	void HandleFirePressed();
	void HandleFireReleased();
	void HandleJump();

	UPROPERTY(EditAnywhere, Category = Movement, BlueprintReadWrite)
	float Speed = 1000.0f;

	UPROPERTY(EditAnywhere, Category = Movement)
	float Gravity = 900.0f;

	UPROPERTY(EditAnywhere, Category = Movement)
	float MouseSensitivity = 1.0f;

	UPROPERTY(EditAnywhere, Category = Movement)
	float MouseYClamp = 89.0f;

	UPROPERTY(EditAnywhere, Category = Movement)
	float JumpForce = 2000.0f;

	UFUNCTION(BlueprintCallable)
	void ActiveInput(bool isActive);

	UFUNCTION(BlueprintCallable)
	void ZeroInputVector();
	
private:
	FVector InputVector = FVector::ZeroVector;
	FVector LookVector = FVector::ZeroVector;
	FVector CurrentGravity = FVector::ZeroVector;
	
	bool bIsGrounded = false;
	bool bActiveInput = true;
};
