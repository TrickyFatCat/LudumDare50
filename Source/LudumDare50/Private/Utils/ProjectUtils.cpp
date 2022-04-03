// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 


#include "Utils/ProjectUtils.h"

#include "Projectiles/ProjectileBase.h"


void UProjectUtils::SpawnProjectile(TSubclassOf<AProjectileBase> ProjectileClass,
                                    AActor* Owner,
                                    const FVector& Position,
                                    const FVector& Direction,
                                    const float Damage)
{
	const FTransform SpawnTransform(FRotator::ZeroRotator, Position);
	AProjectileBase* Projectile = Owner->GetWorld()->SpawnActorDeferred<AProjectileBase>(
		ProjectileClass,
		SpawnTransform);

	if (Projectile)
	{
		Projectile->SetDirectionAndDamage(Direction, nullptr, Damage);
		Projectile->SetOwner(Owner);
		Projectile->FinishSpawning(SpawnTransform);
	}
}
