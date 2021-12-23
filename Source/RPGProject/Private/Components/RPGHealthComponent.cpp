// Training project created by Daytek


#include "Components/RPGHealthComponent.h"


URPGHealthComponent::URPGHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URPGHealthComponent::SetHealth(float Health)
{
	CurrentHealth = FMath::Clamp(Health, 0.0f, MaxHealth);
	OnHealthChange.Broadcast();
	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}

void URPGHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	check(MaxHealth > 0);
	CurrentHealth = MaxHealth;
	AActor* ComponentOwner = GetOwner();
	ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &URPGHealthComponent::OnTakeAnyDamage);
}

void URPGHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                          AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0 || !GetWorld() || IsDead()) return;
	SetHealth(CurrentHealth - Damage);
	GetWorld()->GetTimerManager().ClearTimer(AutoHealTimer);
	if (OnAutoHeal && !IsDead())
	{
		GetWorld()->GetTimerManager().SetTimer(AutoHealTimer, this, &URPGHealthComponent::AutoHealthActor, AutoHealRate, true, FirstHealDelay);
	}
}

void URPGHealthComponent::AutoHealthActor()
{
	SetHealth(CurrentHealth + HealModifier);
	if (FMath::IsNearlyEqual(CurrentHealth, MaxHealth) && GetWorld()) GetWorld()->GetTimerManager().ClearTimer(AutoHealTimer);
}
