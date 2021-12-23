#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RPGBaseCharacter.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

class UCameraComponent;
class USpringArmComponent;
class URPGHealthComponent;

UCLASS()
class RPGPROJECT_API ARPGBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARPGBaseCharacter(const FObjectInitializer& ObjInit);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	URPGHealthComponent* HeathComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rotate Mesh")
	float SpeedRotateMesh = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	FVector2D LandedDamageVelocity{600.0f, 1200.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	FVector2D LandedDamage{10.0f, 100.0f};

	virtual void BeginPlay() override;;
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	FVector MoveVector = {0.0f, 0.0f, 0.0f};

	void MoveForward(const float Axis);
	void MoveRight(const float Axis);
	void RotateToMovement();
	void StartRun();
	void StopRun();

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
};
