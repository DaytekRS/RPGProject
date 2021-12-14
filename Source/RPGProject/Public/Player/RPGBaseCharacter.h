#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RPGBaseCharacter.generated.h"

UCLASS()
class RPGPROJECT_API ARPGBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARPGBaseCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
