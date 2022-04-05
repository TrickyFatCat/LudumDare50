// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnMonsterActor.generated.h"

class UFXController;
class USphereComponent;
UENUM(BlueprintType)
enum class EWaveState: uint8
{
	Ready = 0,
	InSpawn,
	Frozen,
	Block
};

UCLASS()
class LUDUMDARE50_API ASpawnMonsterActor : public AActor
{
	GENERATED_BODY()

public:
	ASpawnMonsterActor();

	bool Spawn(UClass* Monster);

	UFUNCTION(BlueprintCallable)
	void Lock() { State = EWaveState::Block; };

	UFUNCTION(BlueprintCallable)
	void Unlock() { State = EWaveState::Ready; };

	int GetWaveGroup() const { return WaveId; };

protected:
	UPROPERTY(VisibleAnywhere, Category="Wave")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UFXController* ProjectileFX = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wave")
	int WaveId = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wave")
	float FreezingTime = 1.0f;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int OtherBodyIndex
	);

private:
	UPROPERTY(EditAnywhere, Category="Wave")
	EWaveState State = EWaveState::Ready;

	FTimerHandle TimerHandle;
    
	bool bIsBlocked = false;
	
	void RemoveFreeze() { if (State != EWaveState::Block) State = EWaveState::Ready; };
};