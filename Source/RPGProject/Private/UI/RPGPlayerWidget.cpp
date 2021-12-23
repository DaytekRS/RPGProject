// Training project created by Daytek


#include "UI/RPGPlayerWidget.h"

#include "Components/RPGHealthComponent.h"

float URPGPlayerWidget::GetHealthProcent() const
{
	auto HealthComponent = GetComponent<URPGHealthComponent>();
	return HealthComponent ? HealthComponent->GetHealthProcent() : 0.0f;
}

template <typename T>
T* URPGPlayerWidget::GetComponent() const
{
	const auto Character = GetOwningPlayerPawn();
	if (!Character) return  nullptr;

	const auto Component = Cast<T>(Character->GetComponentByClass(T::StaticClass()));
	return Component;
}