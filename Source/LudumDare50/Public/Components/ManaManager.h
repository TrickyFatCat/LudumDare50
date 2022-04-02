// "Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. "

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Objects/EntityResource.h"
#include "ManaManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnManaChangedSignature, float, NewMana, float, DeltaMana);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMaxManaChagedSignature, float, NewMaxMana, float, DeltaMaxHeath);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE50_API UManaManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UManaManager();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable, Category="Mana")
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintCallable, Category="Mana")
	FOnMaxManaChagedSignature OnMaxManaChanged;
	UFUNCTION(BlueprintCallable, Category="Mana")
	float GetMana() const { return ManaObject->GetValue(); }

	UFUNCTION(BlueprintCallable, Category="Mana")
	float GetMaxMana() const { return ManaObject->GetValueMax(); }

	UFUNCTION(BlueprintCallable, Category="Mana")
	float GetNormalizedMana() const { return ManaObject->GetNormalizedValue(); }

	UFUNCTION(BlueprintCallable, Category="Mana")
	void DecreaseMana(const float Amount);

	UFUNCTION(BlueprintCallable, Category="Mana")
	void IncreaseMana(const float Amount, const bool bClampToMax = true);

	UFUNCTION(BlueprintCallable, Category="Mana")
	void DecreaseMaxMana(const float Amount, const bool bClampCurrentMana = true);

	UFUNCTION(BlueprintCallable, Category="Mana")
	void IncreaseMaxMana(const float Amount, const bool bClampCurrentMana = true);

	UFUNCTION(BlueprintSetter, Category="Mana")
	void SetManaData(UPARAM(DisplayName = "NewManaData") const FResourceData& NewData);

	UFUNCTION(BlueprintGetter, Category="Mana")
	FResourceData GetManaData() const { return ManaData; }

	UFUNCTION(BlueprintGetter, Category="Mana")
	float GetGeneralManaModifier() const { return GeneralManaModifier; }

	UFUNCTION(BlueprintSetter, Category="Mana")
	void SetGeneralManaModifier(const float NewModifier);

protected:
	UFUNCTION()
	void BroadcastOnManaChanged(const float NewMana, const float DeltaMana);

	UFUNCTION()
	void BroadcastOnMaxManaChanged(const float NewMaxMana, const float DeltaMaxMana);

	UPROPERTY(EditAnywhere,
		BlueprintGetter=GetManaData,
		BlueprintSetter=SetManaData,
		Category="Mana",
		meta=(AllowPrivateAccess="true"))
	FResourceData ManaData;

	UPROPERTY(BlueprintReadOnly, Category="Mana")
	UEntityResource* ManaObject = nullptr;

	UPROPERTY(VisibleAnywhere,
		BlueprintGetter=GetGeneralManaModifier,
		BlueprintSetter=SetGeneralManaModifier,
		Category="Mana")
	float GeneralManaModifier = 1.f;
};
