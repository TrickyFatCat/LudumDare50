// "Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. "


#include "Components/BaseAbility.h"

#include "Components/ManaManager.h"
#include "GameFramework/Character.h"


UBaseAbility::UBaseAbility()
{
	PrimaryComponentTick.bCanEverTick = true;
}


bool UBaseAbility::ActivateAbility()
{
	if (bIsActivated) return false;

	if (CooldownDuration > 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UBaseAbility::FinishCooldown, CooldownDuration, false);
	}

	 if (ManaCost > 0.f)
	 {
		 UManaManager* ManaManager = GetOwner()->FindComponentByClass<UManaManager>();

	 	if (ManaManager)
	 	{
	 		if (ManaManager->GetMana() < ManaCost)
	 		{
	 			return false;
	 		}
	 		
	 		ManaManager->DecreaseMana(ManaCost);
	 	}
	 }
	
	bIsActivated = true;
	OnAbilityActivated.Broadcast();
	return true;
}

bool UBaseAbility::DeactivateAbility()
{
	if (!bIsActivated) return false;

	bIsActivated = false;
	OnAbilityDeactivated.Broadcast();
	return true;
}

void UBaseAbility::BeginPlay()
{
	Super::BeginPlay();
}

void UBaseAbility::ActivateEffect_Implementation()
{
}

void UBaseAbility::DeactivateEffect_Implementation()
{
}

void UBaseAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBaseAbility::FinishCooldown()
{
	DeactivateAbility();
}

