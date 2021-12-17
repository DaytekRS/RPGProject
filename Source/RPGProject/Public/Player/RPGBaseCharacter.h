#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RPGBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class RPGPROJECT_API ARPGBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARPGBaseCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rotate Mesh")
	float SpeedRotateMesh = 3.0f;

	virtual void BeginPlay() override;;
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	FVector MoveVector = {0.0f, 0.0f, 0.0f};

	void MoveForward(const float Axis);
	void MoveRight(const float Axis);
	void RotateToMovement();
};
