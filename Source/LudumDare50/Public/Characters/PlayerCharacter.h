// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class LUDUMDARE50_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	UCameraComponent* CameraComponent = nullptr;
	
public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
protected:
	UFUNCTION(BlueprintNativeEvent, Category="Abilities")
	void ActivateAbility1();

	UFUNCTION(BlueprintNativeEvent, Category="Abilities")
	void ActivateAbility2();
	
	UFUNCTION(BlueprintNativeEvent, Category="Abilities")
	void ActivateAbility3();
	
	UFUNCTION(BlueprintNativeEvent, Category="Abilities")
	void ActivateAbility4();
	
private:
	UFUNCTION()
	void MoveForward(const float AxisValue);

	UFUNCTION()
	void MoveRight(const float AxisValue);

	void GetMovementRotation(FRotator& Rotator) const;
};
