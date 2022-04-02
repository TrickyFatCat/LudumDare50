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
	                      LifeTimerDuration - ElapsedDuration,
	                      false);
}

void ULifeTimeComponent::StopLifeTimer()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (!TimerManager.IsTimerActive(LifeTimerHandle)) return;

	ElapsedDuration = TimerManager.GetTimerRemaining(LifeTimerHandle);
	TimerManager.ClearTimer(LifeTimerHandle);
	TimerManager.SetTimer(RestoreTimerHandle,
	                      this,
	                      &ULifeTimeComponent::RestoreTime,
	                      UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
	                      true,
	                      1.5f);
}

void ULifeTimeComponent::DamageOwner()
{
	UDamageControllerComponent* DamageControllerComponent = GetOwner()->FindComponentByClass<
		UDamageControllerComponent>();

	if (!DamageControllerComponent) return;

	UGameplayStatics::ApplyDamage(GetOwner(), DamageControllerComponent->GetHealth(), nullptr, nullptr, nullptr);
}

void ULifeTimeComponent::RestoreTime()
{
	if (ElapsedDuration <= 0.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(RestoreTimerHandle);
	}

	ElapsedDuration -= UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
}
