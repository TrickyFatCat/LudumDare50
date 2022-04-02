// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 


#include "Pickups/PickupMana.h"

#include "Components/ManaManager.h"

bool APickupMana::ActivatePickupEffect_Implementation(AActor* TargetActor)
{
	if (!TargetActor) return false;

	UManaManager* ManaManager = TargetActor->FindComponentByClass<UManaManager>();

	if (!ManaManager) return false;

	if (ManaManager->GetNormalizedMana() >= 1.f) return false;

	ManaManager->IncreaseMana(RestorePower, bClampToMaxMana);
	
	return true;
}
