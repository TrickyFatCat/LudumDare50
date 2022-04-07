// "Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. "


#include "Components/LifeTimeComponent.h"

#include "Components/DamageControllerComponent.h"
#include "Kismet/GameplayStatics.h"


ULifeTimeComponent::ULifeTimeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULifeTimeComponent::SetLifeTimeDuration(const float Value)
{
	if (Value <= 0.f) return;

	LifeTimerDuration = Value;
}


float ULifeTimeComponent::GetNormalizedTime() const
{
	const FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	const float RemainingTime = TimerManager.IsTimerActive(LifeTimerHandle)
		                            ? TimerManager.GetTimerRemaining(LifeTimerHandle)
		                            : RemainingLifeTime;
	return bIsInevitable ? 0.f : RemainingTime / LifeTimerDuration;
}

float ULifeTimeComponent::GetRemainingTime() const
{
	const FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	const float RemainingTime = TimerManager.IsTimerActive(LifeTimerHandle)
		                            ? TimerManager.GetTimerRemaining(LifeTimerHandle)
		                            : RemainingLifeTime;
	return bIsInevitable ? 0.f : RemainingTime;
}

bool ULifeTimeComponent::IncreaseRemainingTime(const float Amount)
{
	if (Amount <= 0.f || RemainingLifeTime <= 0.f || GetNormalizedTime() >= 1.f) return false;

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (TimerManager.IsTimerActive(LifeTimerHandle))
	{
		RemainingLifeTime = TimerManager.GetTimerRemaining(LifeTimerHandle);
		TimerManager.ClearTimer(LifeTimerHandle);
		RemainingLifeTime += Amount;
		RemainingLifeTime = FMath::Min(RemainingLifeTime, LifeTimerDuration);
		TimerManager.SetTimer(LifeTimerHandle,
		                      this,
		                      &ULifeTimeComponent::DamageOwner,
		                      RemainingLifeTime,
		                      false);
		return true;
	}

	RemainingLifeTime += Amount;
	RemainingLifeTime = FMath::Min(RemainingLifeTime, LifeTimerDuration);
	return true;
}

bool ULifeTimeComponent::DecreaseRemainingTime(const float Amount)
{
	if (Amount <= 0.f || RemainingLifeTime <= 0.f) return false;

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (TimerManager.IsTimerActive(LifeTimerHandle))
	{
		RemainingLifeTime -= TimerManager.GetTimerRemaining(LifeTimerHandle) + Amount;
		TimerManager.ClearTimer(LifeTimerHandle);

		if (RemainingLifeTime <= 0.f)
		{
			DamageOwner();
			return true;
		}

		TimerManager.SetTimer(LifeTimerHandle,
		                      this,
		                      &ULifeTimeComponent::DamageOwner,
		                      RemainingLifeTime,
		                      false);
		return true;
	}

	RemainingLifeTime -= Amount;

	if (RemainingLifeTime <= 0.f)
	{
		DamageOwner();
		return true;
	}

	return true;
}

void ULifeTimeComponent::BeginPlay()
{
	Super::BeginPlay();
}

void ULifeTimeComponent::TickComponent(float DeltaTime,
                                       ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULifeTimeComponent::StartLifeTimer()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (TimerManager.IsTimerActive(LifeTimerHandle)) return;

	if (TimerManager.IsTimerActive(RestoreTimerHandle))
	{
		TimerManager.ClearTimer(RestoreTimerHandle);
	}

	TimerManager.SetTimer(LifeTimerHandle,
	                      this,
	                      &ULifeTimeComponent::DamageOwner,
	                      RemainingLifeTime,
	                      false);
}

void ULifeTimeComponent::StopLifeTimer()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (!TimerManager.IsTimerActive(LifeTimerHandle)) return;

	RemainingLifeTime = TimerManager.GetTimerRemaining(LifeTimerHandle);
	TimerManager.ClearTimer(LifeTimerHandle);
	TimerManager.SetTimer(RestoreTimerHandle,
	                      this,
	                      &ULifeTimeComponent::RestoreTime,
	                      UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
	                      true,
	                      RestoreStartDelay);
}

void ULifeTimeComponent::DamageOwner()
{
	UDamageControllerComponent* DamageControllerComponent = GetOwner()->FindComponentByClass<
		UDamageControllerComponent>();

	if (!DamageControllerComponent) return;

	UGameplayStatics::ApplyDamage(GetOwner(), DamageControllerComponent->GetHealth(), nullptr, nullptr, nullptr);
	bIsInevitable = true;
}

void ULifeTimeComponent::RestoreTime()
{
	if (RemainingLifeTime >= LifeTimerDuration)
	{
		GetWorld()->GetTimerManager().ClearTimer(RestoreTimerHandle);
	}

	RemainingLifeTime += UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * RestoreTimeFactor;
}
