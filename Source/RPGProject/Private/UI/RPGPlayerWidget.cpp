// Training project created by Daytek


#include "UI/RPGPlayerWidget.h"

#include "RPGBaseCharacter.h"
#include "Components/RPGHealthComponent.h"

float URPGPlayerWidget::GetHealthProcent() const
{
	const auto HealthComponent = GetComponent<URPGHealthComponent>();
	return HealthComponent ? HealthComponent->GetHealthProcent() : 0.0f;
}

 bool URPGPlayerWidget::GetInteractiveDate(FInteractiveData& InteractiveData) const
{
	const auto Character = Cast<ARPGBaseCharacter>(GetOwningPlayerPawn());
	if (!Character) return  false;
	return Character->GetInteractiveData(InteractiveData);
}

template <typename T>
T* URPGPlayerWidget::GetComponent() const
{
	const auto Character = GetOwningPlayerPawn();
	if (!Character) return  nullptr;

	const auto Component = Cast<T>(Character->GetComponentByClass(T::StaticClass()));
	return Component;
}
