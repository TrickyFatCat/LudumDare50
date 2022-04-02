// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RandomLocationNode.generated.h"

UCLASS()
class LUDUMDARE50_API URandomLocationNode : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	URandomLocationNode();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	float Radius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector LocationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	bool SelfCenter = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta = (EditCondition = "SelfCenter == false" ))
	FBlackboardKeySelector CenterActorKey;
};
