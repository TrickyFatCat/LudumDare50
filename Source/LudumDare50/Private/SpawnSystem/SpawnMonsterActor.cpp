// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 


#include "SpawnSystem/SpawnMonsterActor.h"

#include "Characters/EnemyCharacter.h"
#include "Components/SphereComponent.h"
#include "Navigation/PathFollowingComponent.h"

ASpawnMonsterActor::ASpawnMonsterActor()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(100.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	SetRootComponent(CollisionComponent);

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASpawnMonsterActor::OnOverlap);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASpawnMonsterActor::OnEndOverlap);
}

bool ASpawnMonsterActor::Spawn(UClass* Monster)
{
	if (bIsBlocked || State != EWaveState::Ready || GetWorld() == nullptr) return false;

	State = EWaveState::InSpawn;

	const auto Location = GetActorLocation();
	const auto Rotation = GetActorRotation();
	const auto Actor = GetWorld()->SpawnActor(Monster, &Location, &Rotation);
	Cast<AEnemyCharacter>(Actor)->GetMesh()->SetVisibility(true);

	State = EWaveState::Frozen;

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpawnMonsterActor::RemoveFreeze, FreezingTime);

	return Actor != nullptr;
}

void ASpawnMonsterActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASpawnMonsterActor::OnOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	bIsBlocked = true;
}

void ASpawnMonsterActor::OnEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int OtherBodyIndex)
{
	TArray<AActor*> OutOverlappingActors;
	GetOverlappingActors(OutOverlappingActors, {ABaseCharacter::StaticClass()});
	if (OutOverlappingActors.Num() == 0 ) bIsBlocked = false;
}
