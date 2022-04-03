// "Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. "

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseAbility.generated.h"

class UAnimMontage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityActivatedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityDeactivatedSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE50_API UBaseAbility : public UActorComponent
{
	GENERATED_BODY()

public:
	UBaseAbility();

	UPROPERTY(BlueprintAssignable, Category="Ability")
	FOnAbilityActivatedSignature OnAbilityActivated;
	
	UPROPERTY(BlueprintAssignable, Category="Ability")
	FOnAbilityDeactivatedSignature OnAbilityDeactivated;

	UFUNCTION(BlueprintCallable, Category="Ability")
	bool ActivateAbility();
	
	UFUNCTION(BlueprintCallable, Category="Ability")
	bool DeactivateAbility();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, Category="Ability");
	bool bIsActivated = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	UAnimMontage* AbilityMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	float CooldownDuration = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	float ManaCost = 0.f;

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle CooldownTimerHandle;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Ability")
	void ActivateEffect();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Ability")
	void DeactivateEffect();

public:
	virtual void TickComponent(float DeltaTime,
	                           ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION()
	void FinishCooldown();
};
