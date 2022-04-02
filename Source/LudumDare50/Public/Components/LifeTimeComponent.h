// "Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. "

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LifeTimeComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE50_API ULifeTimeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULifeTimeComponent();

	UFUNCTION(BlueprintSetter, Category="LifeTime")
	void SetLifeTimeDuration(const float Value);

	UFUNCTION(BlueprintGetter, Category="LifeTime")
	float GetLifeTimeDuration() const { return LifeTimerDuration; }

	UFUNCTION(BlueprintCallable, Category="LifeTime")
	float GetNormalizedTime() const;

	UFUNCTION(BlueprintCallable, Category="LifeTime")
	bool IncreaseRemainingTime(const float Amount);

	UFUNCTION(BlueprintCallable, Category="LifeTime")
	bool DecreaseRemainingTime(const float Amount);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category="LifeTime")
	FTimerHandle LifeTimerHandle;

	UPROPERTY(BlueprintReadOnly, Category="LifeTime")
	FTimerHandle RestoreTimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="LifeTime")
	float LifeTimerDuration = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="LifeTime")
	float RestoreStartDelay = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="LifeTime")
	float RestoreTimeFactor = 1.f;

	UPROPERTY(BlueprintReadOnly, Category="LifeTime")
	float RemainingLifeTime = LifeTimerDuration;

public:
	virtual void TickComponent(float DeltaTime,
	                           ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="LifeTime")
	void StartLifeTimer();

	UFUNCTION(BlueprintCallable, Category="LifeTime")
	void StopLifeTimer();

	UFUNCTION()
	void DamageOwner();

	UFUNCTION()
	void RestoreTime();
};
