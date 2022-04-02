// Copyright (c) 2021 Artyom "Tricky Fat Cat" Volkov (tricky.fat.cat@gmail.com)


#include "Core/Session/SessionPlayerController.h"

#include "Core/Session/SessionGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/BaseUserWidget.h"

ASessionPlayerController::ASessionPlayerController()
{
}

void ASessionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (CrosshairWidgetClass)
	{
		CrosshairWidget = CreateWidget<UBaseUserWidget>(GetWorld(), CrosshairWidgetClass);
		SetMouseCursorWidget(EMouseCursor::Crosshairs, CrosshairWidget);
	}

	UWorld* World = GetWorld();

	if (World)
	{
		ASessionGameMode* GameMode = Cast<ASessionGameMode>(World->GetAuthGameMode());

		if (GameMode)
		{
			GameMode->OnSessionStateChanged.AddDynamic(this, &ASessionPlayerController::OnSessionStateChanged);
		}
	}

	bShowMouseCursor = false;
	SetTickableWhenPaused(true);
}

void ASessionPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASessionPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	FInputActionBinding& PauseBinding = InputComponent->BindAction("Pause",
	                                                               IE_Pressed,
	                                                               this,
	                                                               &ASessionPlayerController::PauseGame);
	PauseBinding.bExecuteWhenPaused = true;
}

void ASessionPlayerController::OnSessionStateChanged(const ESessionState NewState)
{
	auto ToggleInput = [&](const bool bEnableInput, const bool bShowCursor, const FInputModeDataBase& InputMode)
	{
		bEnableInput ? EnableInput(this) : DisableInput(this);
		bShowMouseCursor = bShowCursor;
		SetInputMode(InputMode);
	};
	
	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	
	switch (NewState)
	{
	case ESessionState::Progress:
		CurrentMouseCursor = EMouseCursor::Crosshairs;
		ToggleInput(true, bShowCursorOnStart, InputMode);
		break;

	case ESessionState::GameOver:
		CurrentMouseCursor = EMouseCursor::Default;
		ToggleInput(false, true, FInputModeUIOnly());
		StopMovement();
		GetPawn()->TurnOff();
		break;

	case ESessionState::Pause:
		CurrentMouseCursor = EMouseCursor::Default;
		ToggleInput(true, true, FInputModeGameAndUI());
		break;

	default:
		CurrentMouseCursor = EMouseCursor::Crosshairs;
		ToggleInput(false, true, InputMode);
		break;
	}
}

void ASessionPlayerController::PauseGame()
{
	IsPaused() ? UGameplayStatics::SetGamePaused(GetWorld(), false) : UGameplayStatics::SetGamePaused(GetWorld(), true);
}
