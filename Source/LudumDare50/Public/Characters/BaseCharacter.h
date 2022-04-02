// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UDamageControllerComponent;

UCLASS()
class LUDUMDARE50_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	UDamageControllerComponent* DamageController = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animations")
	UAnimMontage* DeathMontage = nullptr;

	UFUNCTION()
	void PlayDeathMontage(AController* DeathInstigator, AActor* DeathCauser, const UDamageType* DamageType);

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Character")
	void OnDeathFinished();
};
