#include "Player/RPGBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ARPGBaseCharacter::ARPGBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

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
}

void ARPGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ARPGBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARPGBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ARPGBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ARPGBaseCharacter::AddControllerYawInput);
}

void ARPGBaseCharacter::MoveForward(const float Axis)
{
	AddMovementInput(GetActorForwardVector(), Axis);
}

void ARPGBaseCharacter::MoveRight(const float Axis)
{
	AddMovementInput(GetActorRightVector(), Axis);
}
