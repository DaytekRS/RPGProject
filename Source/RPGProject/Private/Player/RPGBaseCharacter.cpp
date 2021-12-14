#include "Player/RPGBaseCharacter.h"

ARPGBaseCharacter::ARPGBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ARPGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
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
}

void ARPGBaseCharacter::MoveForward(const float Axis)
{
	AddMovementInput(GetActorForwardVector(), Axis);
}

void ARPGBaseCharacter::MoveRight(const float Axis)
{
	AddMovementInput(GetActorRightVector(), Axis);
}

