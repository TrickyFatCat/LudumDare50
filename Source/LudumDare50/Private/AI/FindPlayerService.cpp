// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 


#include "AI/FindPlayerService.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Components/DamageControllerComponent.h"

UFindPlayerService::UFindPlayerService()
{
	NodeName = "Find Player";
}

void UFindPlayerService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (
		Blackboard &&
		GetWorld() != nullptr &&
		GetWorld()->GetFirstPlayerController() != nullptr &&
		GetWorld()->GetFirstPlayerController()->GetPawn() != nullptr
	)
	{
		const auto Control =
			GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UDamageControllerComponent>();

		Blackboard->SetValueAsObject(
			PlayerActorKey.SelectedKeyName,
			Control->GetIsDead() ? nullptr : GetWorld()->GetFirstPlayerController()->GetPawn()
		);
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
