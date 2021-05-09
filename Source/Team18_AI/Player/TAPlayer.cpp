#include "TAPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

ATAPlayer::ATAPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	MyCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = MyCapsule;
	
	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	MyCamera->SetupAttachment(MyCapsule);
}

void ATAPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ATAPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind Inputs
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATAPlayer::HandleFirePressed);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ATAPlayer::HandleFireReleased);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATAPlayer::HandleJump);

	// Bind Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &ATAPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATAPlayer::MoveRight);

	// Bind Looking
	PlayerInputComponent->BindAxis("LookUp", this, &ATAPlayer::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ATAPlayer::LookRight);
}

void ATAPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FHitResult Hit;
	
	// Gravity
	CurrentGravity.Z -= Gravity * DeltaTime;
	AddActorWorldOffset(CurrentGravity, true, &Hit);
	if(Hit.bBlockingHit)
	{
			CurrentGravity.Z = 0;
			bIsGrounded = true;
	}
	
	// Movement
	if(!InputVector.IsNearlyZero())
	{
		FVector Forward = FVector::VectorPlaneProject(MyCamera->GetForwardVector(), FVector::UpVector) * InputVector.X;
		FVector Right = MyCamera->GetRightVector() * InputVector.Y;
		
		FVector Velocity = (Forward + Right).GetSafeNormal() * Speed * DeltaTime;

		// Iterative delta solving
		const int MaxIterations = 10;
		int IterationCount = 0;
		FVector DeltaMove = Velocity * DeltaTime;
		
		while(!DeltaMove.IsNearlyZero() && ++IterationCount < MaxIterations)
		{
			Hit.Reset();
			AddActorWorldOffset(DeltaMove, true, &Hit);
			DeltaMove -= DeltaMove * Hit.Time;
		
			// Collision Handling
			if(Hit.bBlockingHit)
			{
				if(Hit.bStartPenetrating)
				{
					FVector DepenetrationVector = Hit.Normal * (Hit.PenetrationDepth + 0.1f);
					AddActorWorldOffset(DepenetrationVector);
					continue;
				}
			
				FVector ImpactVelocity = FVector::DotProduct(Velocity, Hit.Normal) * Hit.Normal;
				Velocity -= ImpactVelocity;
				DeltaMove -= FVector::DotProduct(DeltaMove, Hit.Normal) * Hit.Normal;
			}
		}
	}

	// Looking
	LookVector.Y = FMath::Clamp(LookVector.Y, -MouseYClamp, MouseYClamp);
	
	MyCamera->SetRelativeRotation(FRotator(-LookVector.Y * MouseSensitivity,0,0));
	MyCapsule->SetRelativeRotation(FRotator(0, LookVector.X * MouseSensitivity,0));
}

void ATAPlayer::MoveRight(float Value)
{
	if(bActiveInput)
		InputVector.Y = Value;
}

void ATAPlayer::MoveForward(float Value)
{
	if(bActiveInput)
		InputVector.X = Value;
}

void ATAPlayer::LookRight(float Value)
{
	if(bActiveInput)
		LookVector.X += Value;
}

void ATAPlayer::LookUp(float Value)
{
	if(bActiveInput)
		LookVector.Y += Value;
}

void ATAPlayer::HandleFirePressed()
{
	
}

void ATAPlayer::HandleFireReleased()
{
	
}

void ATAPlayer::HandleJump()
{
	if(!bActiveInput)
		return;
	
	if(bIsGrounded)
	{
		bIsGrounded = false;
		CurrentGravity.Z = JumpForce;
	}
}

void ATAPlayer::ActiveInput(bool isActive)
{
	bActiveInput = isActive;
}

void ATAPlayer::ZeroInputVector()
{
	InputVector = FVector::ZeroVector;
}
