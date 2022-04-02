// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/EnemyPerceptionComponent.h"
#include "EnemyController.generated.h"

UCLASS()
class LUDUMDARE50_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyController();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UEnemyPerceptionComponent* EnemyPerceptionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FName FocusOnKeyName = "PlayerActor";
    
	virtual void OnPossess(APawn* InPawn) override;
	virtual  void Tick(float DeltaTime) override;

private:
	AActor* GetFocusOnActor() const;
};
