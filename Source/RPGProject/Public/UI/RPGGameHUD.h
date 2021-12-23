// Training project created by Daytek

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RPGGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerWidgetClass;
};
