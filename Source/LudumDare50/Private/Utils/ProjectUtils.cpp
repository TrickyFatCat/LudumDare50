// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 


#include "Utils/ProjectUtils.h"

#include "Projectiles/ProjectileBase.h"


void UProjectUtils::SpawnProjectile(TSubclassOf<AProjectileBase> ProjectileClass,
                                    AActor* Owner,
                                    const FVector& Position,
                                    FVector Direction,
                                    const float Damage,
                                    const float Spread,
                                    const int Amount)
{
	for (int32 i = 1; i <= Amount; i++)
	{
		if (i > 1)
		{
			const float SpreadAngleRad = FMath::DegreesToRadians(Spread / 2);
			Direction = FMath::VRandCone(Direction, SpreadAngleRad);
		}
		
		Direction.Z = 0.f;
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
}
