// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Characters/EnemyCharacter.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "SpawnMonsterManager.generated.h"

USTRUCT(BlueprintType)
struct FEnemyData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TSubclassOf<AEnemyCharacter> Enemy;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (ClampMin = "1", UIMin = "1"))
	int Weight;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (ClampMin = "1", UIMin = "1"))
	int Count;
};

USTRUCT(BlueprintType)
struct FWaveData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<TSubclassOf<AEnemyCharacter>> Enemies;

	UPROPERTY(BlueprintReadOnly)
	int MaxEnemies;

	UPROPERTY(BlueprintReadOnly)
	int Spawned;
	
	UPROPERTY(BlueprintReadOnly)
	float DelayTime;

	UPROPERTY(BlueprintReadOnly)
	int MaxAtTime;
};

class ASpawnMonsterActor;
class UBoxComponent;

UCLASS()
class LUDUMDARE50_API ASpawnMonsterManager : public AActor
{
	GENERATED_BODY()

public:	
	ASpawnMonsterManager();

	UFUNCTION(BlueprintCallable)
	void UpdateWave(UDataTable* Data) { Wave = Data; }
	
	UFUNCTION(BlueprintCallable)
	void UpdateWaveDelay(const float Second) { WaveDelayTime = Second; }
	
	UFUNCTION(BlueprintCallable)
	void UpdateWaveMaxAtTime(const float MonsterCount) { WaveMaxAtTime = MonsterCount; }

	UFUNCTION(BlueprintCallable)
	void UpdateWaveRoundTime(const float Second) { RoundTimeDelay = Second; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wave")
	UDataTable* Wave;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wave")
	float WaveDelayTime = 2.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wave")
	int WaveMaxAtTime = 2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wave")
	float RoundTimeDelay = 20.0f;

	void CallSpawn();

	void CallRound();

	FWaveData GenerateEnemies();

	virtual void BeginPlay() override;

private:
	TArray<ASpawnMonsterActor*> SpawnActors;

	FTimerHandle RoundTimerHandle;
	FTimerHandle WaveTimerHandle;

	FWaveData WaveData;
};
