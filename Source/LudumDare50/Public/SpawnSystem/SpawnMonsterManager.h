// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Characters/EnemyCharacter.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "SpawnMonsterManager.generated.h"

USTRUCT(BlueprintType)
struct FWaveData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TSubclassOf<AEnemyCharacter> Enemy;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (ClampMin = "1", UIMin = "1"))
	int Weight;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (ClampMin = "1", UIMin = "1"))
	int MaxCount;
};

class ASpawnMonsterActor;
class UBoxComponent;

UCLASS()
class LUDUMDARE50_API ASpawnMonsterManager : public AActor
{
	GENERATED_BODY()

public:	
	ASpawnMonsterManager();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Manager")
	TArray<UDataTable*> Waves;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Manager")
	float DelayTime = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Manager")
	int MaxMonsterOnLevel = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Manager")
	TSubclassOf<AEnemyCharacter> TestEnemyClass;

	void CallSpawn();

	virtual void BeginPlay() override;

private:
	TArray<ASpawnMonsterActor*> SpawnActors;

	FTimerHandle TimerHandle;
};
