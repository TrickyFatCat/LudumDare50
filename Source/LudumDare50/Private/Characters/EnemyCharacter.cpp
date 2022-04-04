// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 


#include "Characters/EnemyCharacter.h"
#include "Characters/EnemyController.h"
#include "Components/DamageControllerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = AEnemyController::StaticClass();
	
    if (GetCharacterMovement()) {
        bUseControllerRotationYaw = false;
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	DamageController->OnDeath.AddDynamic(this, &AEnemyCharacter::SpawnPickup);
}

void AEnemyCharacter::SpawnPickup(AController* DeathInstigator, AActor* DeathCauser, const UDamageType* DamageType)
{
	if (PickupClass)
	{
		const bool bSpawnPickup = FMath::RandRange(0, 100) < DropChance;

		if (bSpawnPickup)
		{
			GetWorld()->SpawnActor<APickupBase>(PickupClass, GetMesh()->GetComponentLocation(), GetActorRotation(), FActorSpawnParameters());
		}
	}
}