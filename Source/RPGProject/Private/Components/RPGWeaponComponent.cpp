// Training project created by Daytek


#include "Components/RPGWeaponComponent.h"

#include "InteractiveInterface.h"
#include "GameFramework/Character.h"

URPGWeaponComponent::URPGWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SpawnStandartWeapon();
}


void URPGWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	if (NeedSpawnStandartWeapon){
		SpawnStandartWeapon();
	}
}

void URPGWeaponComponent::EquipWeapon(ARPGBaseWeapon* Weapon)
{
	ACharacter* Player = Cast<ACharacter>(GetOwner());
	if (!Player) return;
	DetachWeapon(CurrentWeapon);
	AttachWeaponToSocket(Weapon, Player->GetMesh(), *WeaponSocketName);
}

void URPGWeaponComponent::SpawnStandartWeapon()
{
	if (!GetWorld()) return;
	EquipWeapon(GetWorld()->SpawnActor<ARPGBaseWeapon>(WeaponStandartClass));
}

void URPGWeaponComponent::AttachWeaponToSocket(ARPGBaseWeapon* Weapon, USceneComponent* SceneComponent,
	const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
	CurrentWeapon = Weapon;
}

void URPGWeaponComponent::DetachWeapon(ARPGBaseWeapon* Weapon, EDetachmentRule InRule)
{
	if (!Weapon) return;
	const FDetachmentTransformRules DetachmentRules(InRule, false);
	Weapon->DetachFromActor(DetachmentRules);
	const auto InteractiveComponent = Cast<IInteractiveInterface>(Weapon);
	if (InteractiveComponent) InteractiveComponent->InteractiveStop(GetOwner());
	CurrentWeapon = nullptr;
}



