#pragma once

#include "CoreMinimal.h"
#include "InteractiveInterface.h"
#include "RPGBaseWeapon.h"
#include "GameFramework/Character.h"
#include "RPGBaseCharacter.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

class UCameraComponent;
class USpringArmComponent;
class URPGHealthComponent;
class URPGWeaponComponent;
class UChildActorComponent;

UCLASS()
class RPGPROJECT_API ARPGBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARPGBaseCharacter(const FObjectInitializer& ObjInit);

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool GetInteractiveData(FInteractiveData& InteractiveData);

	void EquipWeapon(ARPGBaseWeapon* Weapon) const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmMinimapComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UChildActorComponent*  MapCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	URPGHealthComponent* HeathComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	URPGWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interactive")
	bool NeedSearchInteractive = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interactive",
		meta=(EditCondition = "NeedSearchInteractive"))
	float DistanceSearch = 500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interactive",
		meta=(EditCondition = "NeedSearchInteractive", ClampMin="0.01"))
	float SearchInteractiveRate = 0.3f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rotate Mesh")
	bool NeedRotateMesh = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rotate Mesh",
		meta=(EditCondition = "NeedRotateMesh", ClampMin="0.01"))
	float StepAngleRotateMesh = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rotate Mesh",
		meta=(EditCondition = "NeedRotateMesh", ClampMin="0.01"))
	float RateRotateMesh = 0.015f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	FVector2D LandedDamageVelocity{600.0f, 1200.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	FVector2D LandedDamage{10.0f, 100.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* DeathAnimMontage;

	virtual void BeginPlay() override;;

private:
	FVector MoveVector = {0.0f, 0.0f, 0.0f};
	IInteractiveInterface* FoundInteractiveObject = nullptr;
	FTimerHandle SearchInteractiveTimer, RotateTimer;
	const float RotateDelta = 1.5f;

	void MoveForward(const float Axis);
	void MoveRight(const float Axis);
	void RotateToMovement();
	void StartRun();
	void StopRun();

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
	void OnDeath();

	void SearchInteractive();
	void StartInteractive();
};
