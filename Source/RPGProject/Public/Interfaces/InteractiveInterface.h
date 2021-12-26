#pragma once

#include "CoreMinimal.h"
#include "InteractiveInterface.generated.h"

UENUM(BlueprintType)
enum ETypeInteractive
{
	PickUpItem
};

USTRUCT(BlueprintType)
struct FInteractiveData
{
	GENERATED_USTRUCT_BODY()

	FString Message;
	bool DisplayUseKeyMessage;
	ETypeInteractive Type;
};

UINTERFACE(BlueprintType)
class RPGPROJECT_API UInteractiveInterface : public UInterface
{
	GENERATED_BODY()
};


class RPGPROJECT_API IInteractiveInterface
{
	GENERATED_BODY()

public:
	FInteractiveData GetInteractiveData() { return InteractiveData; }

	UFUNCTION()
	virtual void InteractiveStart(AActor* Actor) = 0;

	UFUNCTION()
	virtual bool IsCanInteractive(AActor* Actor) = 0;

	UFUNCTION()
	virtual void InteractiveStop(AActor* Actor) = 0;

protected:
	FInteractiveData InteractiveData{"Empty message", true, PickUpItem};
};
