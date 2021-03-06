// "Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. "


#include "Projectiles/ProjectileBase.h"

#include "Components/FXController.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileCollision = CreateDefaultSubobject<USphereComponent>("ProjectileCollision");
	SetRootComponent(ProjectileCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->bRotationFollowsVelocity = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	ProjectileMesh->SetupAttachment(GetRootComponent());
	ProjectileMesh->CastShadow = false;

	ProjectileFX = CreateDefaultSubobject<UFXController>("ProjectileFX");
}

void AProjectileBase::BeginPlay()
{
	ProjectileMovement->Velocity = ShotDirection * ProjectileMovement->InitialSpeed;
	ProjectileCollision->IgnoreActorWhenMoving(GetOwner(), true);
	ProjectileCollision->OnComponentHit.AddDynamic(this, &AProjectileBase::OnProjectileHit);
	SetLifeSpan(DefaultLifeSpan);

	if (ProjectileData.bIsExplosive && !ProjectileData.bDamageOwner)
	{
		IgnoredActors.Add(GetOwner());
	}

	if (ProjectileData.bIsBouncing)
	{
		ProjectileMovement->bShouldBounce = ProjectileData.bIsBouncing;
	}
	Super::BeginPlay();
}

void AProjectileBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (EndPlayReason != EEndPlayReason::Destroyed) return;

	if (GetLifeSpan() <= 0.f && ProjectileData.bIsExplosive)
	{
		DealRadialDamage();
		FHitResult HitResult;
		HitResult.ImpactPoint = GetActorLocation();
		ProjectileFX->PlayFXAtPoint(HitResult);
	}
}

void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AProjectileBase::GetProjectileData(FProjectileData& Data) const
{
	Data = ProjectileData;
}

void AProjectileBase::SetDirectionAndDamage(const FVector& Direction,
                                            const TSubclassOf<UDamageType> DamageType,
                                            const int32 Damage)
{
	ShotDirection = Direction;

	if (Damage <= 0) return;

	ProjectileData.Damage = Damage;
}

void AProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent,
                                      AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp,
                                      FVector NormalImpulse,
                                      const FHitResult& Hit)
{
	UWorld* World = GetWorld();

	if (!World) return;

	if (ProjectileData.bIsBouncing && !OtherActor->IsA(APawn::StaticClass())) return;

	ProjectileMovement->StopMovementImmediately();

	if (ProjectileData.bIsExplosive)
	{
		DealRadialDamage();
	}
	else
	{
		if (OtherActor->IsA(GetOwner()->GetClass())) return;
		UGameplayStatics::ApplyDamage(OtherActor,
		                              ProjectileData.Damage,
		                              GetOwnerController(),
		                              this,
		                              nullptr);
	}

	ProjectileFX->PlayFXAtPoint(Hit);
	Destroy();
}

void AProjectileBase::DealRadialDamage()
{
	if (!GetWorld()) return;

	UGameplayStatics::ApplyRadialDamage(GetWorld(),
	                                    ProjectileData.Damage,
	                                    GetActorLocation(),
	                                    ProjectileData.ExplosionRadius,
	                                    nullptr,
	                                    IgnoredActors,
	                                    this,
	                                    GetOwnerController(),
	                                    ProjectileData.bDealFullDamage,
	                                    ECC_GameTraceChannel1);
}

AController* AProjectileBase::GetOwnerController() const
{
	APawn* Pawn = Cast<APawn>(GetOwner());

	return Pawn ? Pawn->GetController() : nullptr;
}
