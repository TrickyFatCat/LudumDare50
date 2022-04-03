// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 


#include "Area/LifeArea.h"

#include "Components/LifeTimeComponent.h"

ALifeArea::ALifeArea()
{
	TriggerComponent = CreateDefaultSubobject<UBaseSphereTriggerComponent>("TriggerComponent");
	TriggerComponent->SetupAttachment(GetRootComponent());
}

void ALifeArea::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &ALifeArea::OnBeginOverlap);
	TriggerComponent->OnComponentEndOverlap.AddDynamic(this, &ALifeArea::OnEndOverlap);
}

void ALifeArea::MoveActor(const float Progress)
{
	SetActorScale3D(FMath::Lerp(InitialScale, TargetScale, Progress));

	Super::MoveActor(Progress);
}

void ALifeArea::ProcessMovementStart()
{
	InitialScale = GetActorScale3D();

	Super::ProcessMovementStart();
}

void ALifeArea::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                               AActor* OtherActor,
                               UPrimitiveComponent* OtherComp,
                               int32 OtherBodyIndex,
                               bool bFromSweep,
                               const FHitResult& SweepResult)
{
	ULifeTimeComponent* LifeTimeComponent = OtherActor->FindComponentByClass<ULifeTimeComponent>();

	if (!LifeTimeComponent) return;

	LifeTimeComponent->StopLifeTimer();
}

void ALifeArea::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
                             AActor* OtherActor,
                             UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex)
{
	ULifeTimeComponent* LifeTimeComponent = OtherActor->FindComponentByClass<ULifeTimeComponent>();

	if (!LifeTimeComponent) return;

	LifeTimeComponent->StartLifeTimer();
}
