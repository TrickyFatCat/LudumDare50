// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Actors/PickupBase.h"
#include "Characters/BaseCharacter.h"
#include "EnemyCharacter.generated.h"

class UBehaviorTree;

UCLASS()
class LUDUMDARE50_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
	UBehaviorTree* BehaviorTreeAsset;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Drop")
	TSubclassOf<APickupBase> PickupClass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Drop", meta=(ClampMin = "0", ClampMax = "100"))
	int32 DropChance = 50;

	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnPickup(AController* DeathInstigator, AActor* DeathCauser, const UDamageType* DamageType);
};
