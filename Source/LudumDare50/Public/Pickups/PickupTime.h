// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Actors/PickupBase.h"
#include "PickupTime.generated.h"

/**
 * 
 */
UCLASS()
class LUDUMDARE50_API APickupTime : public APickupBase
{
	GENERATED_BODY()
	
protected:
	virtual bool ActivatePickupEffect_Implementation(AActor* TargetActor) override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Pickup", meta=(AllowPrivateAccess="true", ClampMin="0.0"))
	float TimeToRestore = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Pickup", meta=(AllowPrivateAccess="true"))
	bool bClampToMaxTime = true;
};
