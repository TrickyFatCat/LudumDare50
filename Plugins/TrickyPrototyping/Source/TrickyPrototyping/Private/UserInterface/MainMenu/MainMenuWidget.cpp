// Copyright (c) 2021 Artyom "Tricky Fat Cat" Volkov (tricky.fat.cat@gmail.com)


#include "UserInterface/MainMenu/MainMenuWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/TransitionScreenWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UserInterface/MainMenu/SplashScreenWidget.h"
#include "Core/TrickyGameInstance.h"

void UMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (TransitionScreen)
	{
		TransitionScreen->OnShowed.AddDynamic(this, &UMainMenuWidget::ProcessTransition);
		TransitionScreen->OnHidden.AddDynamic(this, &UMainMenuWidget::TransitionFinished);
	}

	if (Button_StartGame_1)
	{
		Button_StartGame_1->OnClicked.AddDynamic(this, &UMainMenuWidget::StartLevel1);
	}
	
	if (Button_StartGame_2)
	{
		Button_StartGame_2->OnClicked.AddDynamic(this, &UMainMenuWidget::StartLevel2);
	}
	
	if (Button_StartGame_3)
	{
		Button_StartGame_3->OnClicked.AddDynamic(this, &UMainMenuWidget::StartLevel3);
	}

	if (Button_StartGame_4)
	{
		Button_StartGame_4->OnClicked.AddDynamic(this, &UMainMenuWidget::StartLevel4);
	}

	if (Button_QuitGame)
	{
		Button_QuitGame->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitGame);
	}

	APlayerController* Controller = GetOwningPlayer();

	if (Controller)
	{
		Controller->SetInputMode(FInputModeUIOnly());
		Controller->bShowMouseCursor = false;
	}

	TransitionScreen->SetVisibility(ESlateVisibility::Visible);
	TransitionScreen->Hide();
}

void UMainMenuWidget::TransitionFinished()
{
	SetCursorVisibility(true);
}

void UMainMenuWidget::ProcessTransition()
{
	if (!GetWorld()) return;

	UTrickyGameInstance* GameInstance = GetWorld()->GetGameInstance<UTrickyGameInstance>();

	if (!GameInstance) return;

	switch (Command)
	{
	case ETransitionCommand::Start:
		UGameplayStatics::OpenLevel(this, GameInstance->GetLevelName(StartLevelIndex));
		break;

	case ETransitionCommand::Quit:
		UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
		break;
	}
}

void UMainMenuWidget::OnStartGame(const int32 LevelIndex)
{
	Command = ETransitionCommand::Start;
	SetCursorVisibility(false);
	StartTransition();
	StartLevelIndex = LevelIndex;
}

void UMainMenuWidget::OnQuitGame()
{
	Command = ETransitionCommand::Quit;
	SetCursorVisibility(false);
	StartTransition();
}

void UMainMenuWidget::StartTransition() const
{
	TransitionScreen->SetVisibility(ESlateVisibility::Visible);
	TransitionScreen->Show();
}

void UMainMenuWidget::SetCursorVisibility(const bool bIsVisible) const
{
	APlayerController* Controller = GetOwningPlayer();

	if (Controller)
	{
		Controller->bShowMouseCursor = bIsVisible;
	}
}
