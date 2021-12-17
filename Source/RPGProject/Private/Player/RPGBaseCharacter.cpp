#include "Player/RPGBaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Utils/MathUtil.h"

ARPGBaseCharacter::ARPGBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SocketOffset = FVector(0.0f, 0.0f, 80.0f);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ARPGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(SpringArmComponent);
	check(CameraComponent);
}

void ARPGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateToMovement();
}

void ARPGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ARPGBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARPGBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ARPGBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ARPGBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARPGBaseCharacter::Jump);
}

void ARPGBaseCharacter::MoveForward(const float Axis)
{
	MoveVector.X = Axis;
	AddMovementInput(CameraComponent->GetForwardVector(), Axis);
}

void ARPGBaseCharacter::MoveRight(const float Axis)
{
	MoveVector.Y = Axis;
	AddMovementInput(CameraComponent->GetRightVector(), Axis);
}

void ARPGBaseCharacter::RotateToMovement()
{
	const float DirectionAngle = FUtils::GetAngleDirection(MoveVector);
	if (FMath::IsNearlyEqual(DirectionAngle, -1.0f)) return;

	FVector CameraVector(CameraComponent->GetForwardVector().X, CameraComponent->GetForwardVector().Y, 0.0f);
	CameraVector.Normalize();
	float RotateMeshAngle = FUtils::DegreesBetweenVectors(CameraVector, GetMesh()->GetRightVector());
	RotateMeshAngle = FUtils::NormalizeToCircleAngle(RotateMeshAngle);

	if (!FMath::IsNearlyEqual(DirectionAngle, RotateMeshAngle))
	{
		const float ClockwiseAngle = FUtils::NormalizeToCircleAngle(DirectionAngle - RotateMeshAngle);
		const float AnticlockwiseAngle = FUtils::NormalizeToCircleAngle(RotateMeshAngle - DirectionAngle);
		const float SignStepAngle = (ClockwiseAngle < AnticlockwiseAngle) ? 1 : -1;
		const float AngleToDirection = (ClockwiseAngle < AnticlockwiseAngle) ? ClockwiseAngle : AnticlockwiseAngle;

		float StepAngle = SpeedRotateMesh;
		if (AngleToDirection < StepAngle) StepAngle = AngleToDirection;
		const FRotator Rotator(0.0f, StepAngle * SignStepAngle, 0.0f);
		GetMesh()->AddLocalRotation(Rotator);
	}
}
