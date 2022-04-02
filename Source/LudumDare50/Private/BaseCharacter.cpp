// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/DamageControllerComponent.h"


ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	DamageController = CreateDefaultSubobject<UDamageControllerComponent>("DamageController");
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetVisibility(false, false);
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

