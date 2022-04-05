// "Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. "


#include "Components/FXController.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


UFXController::UFXController()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFXController::BeginPlay()
{
	Super::BeginPlay();
}

void UFXController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UFXController::PlayFXAtPoint(const FHitResult& HitResult)
{
	UWorld* World = GetWorld();

	if (!World) return;
	UGameplayStatics::SpawnEmitterAtLocation(World,
	                                         FxData.ImpactEffect,
	                                         HitResult.ImpactPoint,
	                                         HitResult.ImpactNormal.Rotation(),
	                                         FxData.ImpactScale);

	UGameplayStatics::PlaySoundAtLocation(World, FxData.Sound, HitResult.ImpactPoint);
}
