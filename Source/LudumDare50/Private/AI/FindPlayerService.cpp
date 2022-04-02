// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 


#include "AI/FindPlayerService.h"

#include "BehaviorTree/BlackboardComponent.h"

UFindPlayerService::UFindPlayerService()
{
	NodeName = "Find Player";
}

void UFindPlayerService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		Blackboard->SetValueAsObject(
			PlayerActorKey.SelectedKeyName,
			GetWorld()->GetFirstPlayerController()->GetPawn()
		);
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
