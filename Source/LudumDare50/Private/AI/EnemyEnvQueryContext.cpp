// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 


#include "AI/EnemyEnvQueryContext.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	const auto QueryActor = Cast<AActor>(QueryInstance.Owner.Get());
	const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryActor);
	if (Blackboard == nullptr) return;

	const auto ContextActor = Blackboard->GetValueAsObject(PlayerActorKeyName);
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(ContextActor));
}
