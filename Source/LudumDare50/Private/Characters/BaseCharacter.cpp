// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 


#include "Characters/BaseCharacter.h"
#include "Components/DamageControllerComponent.h"


ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	DamageController = CreateDefaultSubobject<UDamageControllerComponent>("DamageController");
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	DamageController->OnDeath.AddDynamic(this, &ABaseCharacter::PlayDeathMontage);
}

void ABaseCharacter::PlayDeathMontage(AController* DeathInstigator, AActor* DeathCauser, const UDamageType* DamageType)
{
	PlayAnimMontage(DeathMontage);
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
