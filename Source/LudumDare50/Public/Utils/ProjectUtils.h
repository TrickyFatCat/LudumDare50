// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProjectUtils.generated.h"

class AProjectileBase;
/**
 * 
 */
UCLASS()
class LUDUMDARE50_API UProjectUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="ProjectUtils")
	static void SpawnProjectile(TSubclassOf<AProjectileBase> ProjectileClass,
	                            AActor* Owner,
	                            const FVector& Position,
	                            const FVector& Direction,
	                            const float Damage);
};
