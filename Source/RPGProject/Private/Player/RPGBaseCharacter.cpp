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

}

