// Training project created by Daytek

#pragma once

#include "CoreMinimal.h"
#include "Weapons/RPGBaseWeapon.h"
#include "Interfaces/InteractiveInterface.h"
#include "RPGBlackKnightWeapon.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGBlackKnightWeapon : public ARPGBaseWeapon, public IInteractiveInterface
{
	GENERATED_BODY()
public:
	ARPGBlackKnightWeapon();
	virtual void InteractiveStart(AActor* Actor);
	virtual void InteractiveStop(AActor* Actor);
	virtual bool IsCanInteractive(AActor* Actor);
};
