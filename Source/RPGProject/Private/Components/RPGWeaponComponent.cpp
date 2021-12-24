// Training project created by Daytek


#include "Components/RPGWeaponComponent.h"

#include "GameFramework/Character.h"

URPGWeaponComponent::URPGWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SpawnStandartWeapon();
}


void URPGWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnStandartWeapon();
}

void URPGWeaponComponent::EquipWeapon(ARPGBaseWeapon*)
{
	
}

void URPGWeaponComponent::SpawnStandartWeapon()
{
	ACharacter* Player = Cast<ACharacter>(GetOwner());
	if (!Player || !GetWorld()) return;
	CurrentWeapon = GetWorld()->SpawnActor<ARPGBaseWeapon>(WeaponStandartClass);
	AttachWeaponToSocket(CurrentWeapon, Player->GetMesh(), *WeaponSocketName);
}

void URPGWeaponComponent::AttachWeaponToSocket(ARPGBaseWeapon* Weapon, USceneComponent* SceneComponent,
	const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}



