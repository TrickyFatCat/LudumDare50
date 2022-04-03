// "Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. "

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UFXController;

USTRUCT(BlueprintType)
struct FProjectileData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category="Projectile", meta=(ClampMin="0"))
	int32 Damage = 10.f;

	bool bIsBouncing = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile")
	bool bIsExplosive = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile", meta=(EditCondition="bIsExplosive", ClampMin="0"))
	float ExplosionRadius = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile", meta=(EditCondition="bIsExplosive"))
	bool bDealFullDamage = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile", meta=(EditCondition="bIsExplosive"))
	bool bDamageOwner = false;
};

UCLASS()
class LUDUMDARE50_API AProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	AProjectileBase();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category="Projectile")
	void GetProjectileData(FProjectileData& Data) const;

	void SetDirectionAndDamage(const FVector& Direction, const TSubclassOf<UDamageType> DamageType, const int32 Damage);


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	USphereComponent* ProjectileCollision = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* ProjectileMesh = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UFXController* ProjectileFX = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	FProjectileData ProjectileData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Projectile", meta=(AllowPrivateAccess="true"))
	float DefaultLifeSpan = 5.f;

	FVector ShotDirection = FVector::ZeroVector;

	UPROPERTY()
	TArray<AActor*> IgnoredActors;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent,
	                     AActor* OtherActor,
	                     UPrimitiveComponent* OtherComp,
	                     FVector NormalImpulse,
	                     const FHitResult& Hit);

	void DealRadialDamage();

	AController* GetOwnerController() const;
};
