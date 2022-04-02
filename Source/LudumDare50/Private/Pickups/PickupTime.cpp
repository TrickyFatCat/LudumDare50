// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 


#include "Pickups/PickupTime.h"

#include "Components/LifeTimeComponent.h"

bool APickupTime::ActivatePickupEffect_Implementation(AActor* TargetActor)
{
	if (!TargetActor) return false;

	ULifeTimeComponent* LifeTimeComponent = TargetActor->FindComponentByClass<ULifeTimeComponent>();

	if (!LifeTimeComponent) return false;

	if (LifeTimeComponent->GetNormalizedTime() >= 1.f) return false;

	return LifeTimeComponent->IncreaseRemainingTime(TimeToRestore);
}
