// Training project created by Daytek

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapons/RPGBaseWeapon.h"
#include "RPGWeaponComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPGPROJECT_API URPGWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URPGWeaponComponent();
	
	void EquipWeapon(ARPGBaseWeapon* Weapon);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Standart Weapon")
	bool NeedSpawnStandartWeapon = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Standart Weapon", meta=(EditCondition = "NeedSpawnStandartWeapon"))
	TSubclassOf<ARPGBaseWeapon> WeaponStandartClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	FString WeaponSocketName = "WeaponSocket";

	virtual void BeginPlay() override;

private:
	ARPGBaseWeapon* CurrentWeapon;
	
	void SpawnStandartWeapon();
	void AttachWeaponToSocket(ARPGBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void DetachWeapon(ARPGBaseWeapon* Weapon, EDetachmentRule InRule = EDetachmentRule::KeepWorld);
};



