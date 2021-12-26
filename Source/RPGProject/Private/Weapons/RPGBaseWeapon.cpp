// Training project created by Daytek


#include "Weapons/RPGBaseWeapon.h"

#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"

ARPGBaseWeapon::ARPGBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
}

void ARPGBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}


