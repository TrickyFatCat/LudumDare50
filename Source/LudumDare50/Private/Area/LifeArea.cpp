// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 


#include "Area/LifeArea.h"

#include "Components/LifeTimeComponent.h"

ALifeArea::ALifeArea()
{
	TriggerComponent = CreateDefaultSubobject<UBaseSphereTriggerComponent>("TriggerComponent");
	TriggerComponent->SetupAttachment(GetRootComponent());
	TriggerComponent->SetSphereRadius(DefaultRadius);

	EffectMesh = CreateDefaultSubobject<UStaticMeshComponent>("EffectMesh");
	EffectMesh->SetupAttachment(TriggerComponent);
	EffectMesh->SetRelativeScale3D(DefaultEffectScale);
	EffectMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ALifeArea::BeginPlay()
{
	Super::BeginPlay();

	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &ALifeArea::OnBeginOverlap);
	TriggerComponent->OnComponentEndOverlap.AddDynamic(this, &ALifeArea::OnEndOverlap);
}

void ALifeArea::MoveActor(const float Progress)
{
	AnimateScale(Progress);
	Super::MoveActor(Progress);
}

void ALifeArea::ProcessMovementStart()
{
	CalculateRadius();
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

void ALifeArea::CalculateRadius()
{
	InitialRadius = TriggerComponent->GetUnscaledSphereRadius();
	TargetRadius = DefaultRadius * TargetScale;
	InitialEffectScale = EffectMesh->GetRelativeScale3D();
	TargetEffectScale = DefaultEffectScale * TargetScale;
	TargetEffectScale.Z = DefaultEffectScale.Z;
}

void ALifeArea::AnimateScale(const float Progress)
{
	TriggerComponent->SetSphereRadius(FMath::Lerp(InitialRadius, TargetRadius, Progress));
	EffectMesh->SetRelativeScale3D(FMath::Lerp(InitialEffectScale, TargetEffectScale, Progress));
}
