// Training project created by Daytek

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPGBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class RPGPROJECT_API ARPGBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ARPGBaseWeapon();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components");
	USkeletalMeshComponent* WeaponMesh;
	
	virtual void BeginPlay() override;
};
