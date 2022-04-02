// "Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. "


#include "Components/ManaManager.h"


UManaManager::UManaManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UManaManager::BeginPlay()
{
	ManaObject = NewObject<UEntityResource>(this, TEXT("ManaObject"));
	ManaObject->SetResourceData(ManaData);
	ManaObject->OnValueChanged.AddDynamic(this, &UManaManager::BroadcastOnManaChanged);
	ManaObject->OnValueMaxChanged.AddDynamic(this, &UManaManager::BroadcastOnMaxManaChanged);
	
	Super::BeginPlay();
}

void UManaManager::DecreaseMana(const float Amount)
{
	if (Amount <= 0.f || GetMana() <= 0.f) return;

	ManaObject->DecreaseValue(Amount * GeneralManaModifier);
}

void UManaManager::IncreaseMana(const float Amount, const bool bClampToMax)
{
	if (Amount <= 0.f || GetMana() >= GetMaxMana()) return;

	ManaObject->IncreaseValue(Amount, bClampToMax);
}

void UManaManager::DecreaseMaxMana(const float Amount, const bool bClampCurrentMana)
{
	if (Amount <= 0.f) return;

	ManaObject->DecreaseValueMax(Amount, bClampCurrentMana);
}

void UManaManager::IncreaseMaxMana(const float Amount, const bool bClampCurrentMana)
{
	if (Amount <= 0.f) return;

	ManaObject->IncreaseValueMax(Amount, bClampCurrentMana);
}

void UManaManager::SetManaData(const FResourceData& NewData)
{
	ManaData = NewData;
	ManaObject->SetResourceData(NewData);
}

void UManaManager::BroadcastOnManaChanged(const float NewMana, const float DeltaMana)
{
	OnManaChanged.Broadcast(NewMana, DeltaMana);
}

void UManaManager::BroadcastOnMaxManaChanged(const float NewMaxMana, const float DeltaMaxMana)
{
	OnMaxManaChanged.Broadcast(NewMaxMana, DeltaMaxMana);
}

void UManaManager::SetGeneralManaModifier(const float NewModifier)
{
	if (GeneralManaModifier < 0.f) return;

	GeneralManaModifier = NewModifier;
}
