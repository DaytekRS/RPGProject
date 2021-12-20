// Training project created by Daytek

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RPGCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	virtual float GetMaxSpeed() const override;
	UFUNCTION()
	void TurnOnWalkModifier();
	UFUNCTION()
	void TurnOffWalkModifier();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "10.0"))
	float WalkModifier = 2.0f;

private:
	bool IsOnWalkModifier = false;
};
