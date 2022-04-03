// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Actors/FloatingActors/FloatingActorPoints.h"
#include "Components/TriggerComponents/BaseSphereTriggerComponent.h"
#include "LifeArea.generated.h"

/**
 * 
 */
UCLASS()
class LUDUMDARE50_API ALifeArea : public AFloatingActorPoints
{
	GENERATED_BODY()

public:
	ALifeArea();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintSetter, Category="FloatingActor|Points")
	void SetTargetScale(const FVector NewScale) { TargetScale = NewScale; }

	UFUNCTION(BlueprintGetter, Category="FloatingActor|Points")
	FVector GetTargetScale() const { return TargetScale; }

protected:
	UPROPERTY(VisibleAnywhere)
	FVector InitialScale = FVector::OneVector;
	
	UPROPERTY(BlueprintSetter=SetTargetScale, BlueprintGetter=GetTargetScale, Category="FloatingActor|Points")
	FVector TargetScale = FVector::OneVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	UBaseSphereTriggerComponent* TriggerComponent = nullptr;

	virtual void MoveActor(const float Progress) override;

	virtual void ProcessMovementStart() override;
	
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                            AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp,
	                            int32 OtherBodyIndex,
	                            bool bFromSweep,
	                            const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
	                          AActor* OtherActor,
	                          UPrimitiveComponent* OtherComp,
	                          int32 OtherBodyIndex);
};
