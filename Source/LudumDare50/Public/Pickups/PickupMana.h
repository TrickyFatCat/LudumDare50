// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Actors/PickupBase.h"
#include "PickupMana.generated.h"

/**
 * 
 */
UCLASS()
class LUDUMDARE50_API APickupMana : public APickupBase
{
	GENERATED_BODY()
	
protected:
	virtual bool ActivatePickupEffect_Implementation(AActor* TargetActor) override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Pickup", meta=(AllowPrivateAccess="true", ClampMin="0.0"))
	float RestorePower = 25.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Pickup", meta=(AllowPrivateAccess="true"))
	bool bClampToMaxMana= true;
};
