// Training project created by Daytek

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE(FOnHealthChange);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPGPROJECT_API URPGHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URPGHealthComponent();

	UFUNCTION(BlueprintCallable)
	void SetHealth(float Health);

	UFUNCTION(BlueprintCallable)
	float GetHealth() const { return CurrentHealth; };

	UFUNCTION(BlueprintCallable)
	float GetHealthProcent() const { return CurrentHealth / MaxHealth; };

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return FMath::IsNearlyZero(CurrentHealth); }

	FOnHealthChange OnHealthChange;
	FOnDeath OnDeath;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.1"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Auto Heal")
	bool OnAutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Auto Heal", meta=(EditCondition = "OnAutoHeal"))
	float AutoHealRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Auto Heal", meta=(EditCondition = "OnAutoHeal"))
	float HealModifier = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Auto Heal", meta=(EditCondition = "OnAutoHeal"))
	float FirstHealDelay = 10.0f;

	virtual void BeginPlay() override;

private:
	FTimerHandle AutoHealTimer;
	float CurrentHealth;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	                     class AController* InstigatedBy, AActor* DamageCauser);

	void AutoHealthActor();
};
