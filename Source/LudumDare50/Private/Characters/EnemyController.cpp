// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 


#include "Characters/EnemyController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/EnemyCharacter.h"


AEnemyController::AEnemyController()
{
	EnemyPerceptionComponent = CreateDefaultSubobject<UEnemyPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*EnemyPerceptionComponent);
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto Char = Cast<AEnemyCharacter>(InPawn);
	if (Char == nullptr) return;

	RunBehaviorTree(Char->BehaviorTreeAsset);
}

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetFocus(GetFocusOnActor());
}

AActor* AEnemyController::GetFocusOnActor() const
{
	if (GetBlackboardComponent() == nullptr) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
