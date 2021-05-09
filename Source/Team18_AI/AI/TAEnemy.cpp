#include "TAEnemy.h"
#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Movement/TANavMovementComponent.h"

ATAEnemy::ATAEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	Capsule->InitCapsuleSize(55.0f, 96.0f);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Capsule);
	Mesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	NavMovementComponent = CreateDefaultSubobject<UTANavMovementComponent>(TEXT("NavMovement"));
}

void ATAEnemy::BeginPlay()
{
	Super::BeginPlay();

	LastPosition = GetActorLocation();
}

void ATAEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	VelocityMagnitude = FVector::Distance(LastPosition, GetActorLocation());
	LastPosition = GetActorLocation();

	FRotator const CurrentRot = GetActorRotation();
	FVector const CurrentRotVec = FVector(CurrentRot.Pitch, CurrentRot.Yaw, CurrentRot.Roll);
	RotationDeltaMagnitude = FVector::Distance(LastRotation, CurrentRotVec);
	LastRotation = CurrentRotVec;
}

float ATAEnemy::GetDefaultHalfHeight() const
{
	return Capsule->GetScaledCapsuleHalfHeight();
}
