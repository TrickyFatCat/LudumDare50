// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 


#include "AI/AbilityService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BaseAbility.h"

UAbilityService::UAbilityService()
{
	NodeName = "Activate Ability";
}

void UAbilityService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(PlayerActorKey.SelectedKeyName);
	if (Controller) {
		const auto Ability = Controller->GetPawn()->FindComponentByClass<UBaseAbility>();
		if (Ability) HasAim ? Ability->ActivateAbility() : Ability->DeactivateAbility();
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
