// Training project created by Daytek

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGPlayerWidget.generated.h"

UCLASS()
class RPGPROJECT_API URPGPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="UI")
	float GetHealthProcent() const;
	
private:
	template <typename T>
	T* GetComponent() const;
};


