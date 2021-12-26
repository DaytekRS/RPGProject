// Training project created by Daytek


#include "Weapons/RPGBlackKnightWeapon.h"

#include "RPGBaseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"

ARPGBlackKnightWeapon::ARPGBlackKnightWeapon()
{
	InteractiveData.Message = "Подобрать предмет";
	InteractiveData.DisplayUseKeyMessage = true;
	InteractiveData.Type = PickUpItem;
}


void ARPGBlackKnightWeapon::InteractiveStart(AActor* Actor)
{
	ARPGBaseCharacter* Player = Cast<ARPGBaseCharacter>(Actor);
	if (!Player) return;
	WeaponMesh->SetSimulatePhysics(false);
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Player->EquipWeapon(this);
}

void ARPGBlackKnightWeapon::InteractiveStop(AActor* Actor)
{
	ARPGBaseCharacter* Player = Cast<ARPGBaseCharacter>(Actor);
	if (!Player) return;
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Block);
	WeaponMesh->SetSimulatePhysics(true);
}

bool ARPGBlackKnightWeapon::IsCanInteractive(AActor* Actor)
{
	ARPGBaseCharacter* Player = Cast<ARPGBaseCharacter>(Actor);
	if (GetAttachParentActor() || !Player || Player->GetMovementComponent()->IsFalling()) return false;
	return true;
}
