// "Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. "


#include "Components/BaseAbility.h"


UBaseAbility::UBaseAbility()
{
	PrimaryComponentTick.bCanEverTick = true;
}


bool UBaseAbility::ActivateAbility_Implementation()
{
	if (bIsActivated) return false;

	if (CooldownDuration > 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UBaseAbility::FinishCooldown, CooldownDuration, false);
	}

	bIsActivated = true;
	OnAbilityActivated.Broadcast();
	return true;
}

bool UBaseAbility::DeactivateAbility_Implementation()
{
	if (!bIsActivated || CooldownDuration > 0.f) return false;

	bIsActivated = false;
	OnAbilityDeactivated.Broadcast();
	return true;
}

void UBaseAbility::BeginPlay()
{
	Super::BeginPlay();

}


void UBaseAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBaseAbility::FinishCooldown()
{
	DeactivateAbility_Implementation();
}

