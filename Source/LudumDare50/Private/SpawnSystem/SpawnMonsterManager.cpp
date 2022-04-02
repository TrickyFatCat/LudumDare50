// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 


#include "SpawnSystem/SpawnMonsterManager.h"

#include "EngineUtils.h"
#include "Characters/EnemyCharacter.h"
#include "SpawnSystem/SpawnMonsterActor.h"

DECLARE_LOG_CATEGORY_CLASS(LogSpawnMonsterManager, All, All);

ASpawnMonsterManager::ASpawnMonsterManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASpawnMonsterManager::CallSpawn()
{
	for (ASpawnMonsterActor* SpawnActor : SpawnActors)
	{
		if (SpawnActor->Spawn(TestEnemyClass)) break;
	}
}

void ASpawnMonsterManager::BeginPlay()
{
	Super::BeginPlay();

	SpawnActors.Reset();
	for (TActorIterator<ASpawnMonsterActor> It(GetWorld()); It; ++It) { SpawnActors.Add(*It); }
	UE_LOG(LogSpawnMonsterManager, Display, TEXT("Count Spawn: %i."), SpawnActors.Num());

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpawnMonsterManager::CallSpawn, DelayTime, true, 0);
}
