// Training project created by Daytek

#pragma once

#include "CoreMinimal.h"
#include "InteractiveInterface.h"
#include "Blueprint/UserWidget.h"
#include "RPGPlayerWidget.generated.h"

UCLASS()
class RPGPROJECT_API URPGPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="UI")
	float GetHealthProcent() const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool GetInteractiveDate(FInteractiveData& InteractiveData) const;
	
private:
	template <typename T>
	T* GetComponent() const;
};


