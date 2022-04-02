// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 


#include "Characters/PlayerCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ManaManager.h"
#include "Kismet/KismetMathLibrary.h"

APlayerCharacter::APlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);

	ManaManager = CreateDefaultSubobject<UManaManager>("ManaManager");
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	RotateTowardsCursor();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Ability1", IE_Pressed, this, &APlayerCharacter::ActivateAbility1);
	PlayerInputComponent->BindAction("Ability2", IE_Pressed, this, &APlayerCharacter::ActivateAbility2);
	PlayerInputComponent->BindAction("Ability3", IE_Pressed, this, &APlayerCharacter::ActivateAbility3);
	PlayerInputComponent->BindAction("Ability4", IE_Pressed, this, &APlayerCharacter::ActivateAbility4);
}

void APlayerCharacter::ActivateAbility1_Implementation()
{
}

void APlayerCharacter::ActivateAbility2_Implementation()
{
}

void APlayerCharacter::ActivateAbility3_Implementation()
{
}

void APlayerCharacter::ActivateAbility4_Implementation()
{
}

void APlayerCharacter::MoveForward(const float AxisValue)
{
	FRotator Rotation;
	GetMovementRotation(Rotation);
	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(Rotation);
	AddMovementInput(ForwardVector, AxisValue);
}

void APlayerCharacter::MoveRight(const float AxisValue)
{
	FRotator Rotation;
	GetMovementRotation(Rotation);
	const FVector RightVector = UKismetMathLibrary::GetRightVector(Rotation);
	AddMovementInput(RightVector, AxisValue);
}


void APlayerCharacter::GetMovementRotation(FRotator& Rotator) const
{
	Rotator = FRotator(0.f, GetControlRotation().Yaw, 0.f);
}

void APlayerCharacter::RotateTowardsCursor()
{
	const FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ProjectCursorToWorld());
	SetActorRotation(FRotator(0.f, TargetRotation.Yaw, 0.f));
}

FVector APlayerCharacter::ProjectCursorToWorld()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (!PlayerController) return FVector::ZeroVector;

	FVector WorldLocation, WorldDirection, Location;

	if (PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		const bool bPointFound = CalculateProjection(WorldLocation,
		                                             WorldDirection,
		                                             1000.f,
		                                             GetActorLocation(),
		                                             FVector::UpVector,
		                                             Location);

		if (!bPointFound) return FVector::ZeroVector;
	}
	else
	{
		return FVector::ZeroVector;
	}

	return Location;
}

bool APlayerCharacter::CalculateProjection(FVector RayOrigin,
                                           FVector RayDirection,
                                           const float Range,
                                           FVector PlaneOrigin,
                                           FVector PlaneNormal,
                                           FVector& Intersection)
{
	const FVector Vec1 = FVector(((RayDirection * Range) + RayOrigin) - RayOrigin);
	const float Dot1 = FVector::DotProduct(PlaneOrigin - RayOrigin, PlaneNormal);
	const float Dot2 = FVector::DotProduct(Vec1, PlaneNormal);
	Intersection = FVector(RayOrigin + (Vec1 * (Dot1 / Dot2)));

	return Dot2 != 0.f;
}
