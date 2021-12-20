// Training project created by Daytek


#include "Components/RPGCharacterMovementComponent.h"

float URPGCharacterMovementComponent::GetMaxSpeed() const
{
	return IsOnWalkModifier ? Super::GetMaxSpeed() * WalkModifier : Super::GetMaxSpeed();
}

void URPGCharacterMovementComponent::TurnOnWalkModifier()
{
	IsOnWalkModifier = true;
}

void URPGCharacterMovementComponent::TurnOffWalkModifier()
{
	IsOnWalkModifier = false;
}
