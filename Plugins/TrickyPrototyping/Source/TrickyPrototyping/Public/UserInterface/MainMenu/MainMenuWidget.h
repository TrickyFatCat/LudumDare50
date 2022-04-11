// Copyright (c) 2021 Artyom "Tricky Fat Cat" Volkov (tricky.fat.cat@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/TrickyCoreTypes.h"
#include "MainMenuWidget.generated.h"

class UButton;
class UImage;
class USplashScreenWidget;
class UTransitionScreenWidget;

/**
 * 
 */



UCLASS()
class TRICKYPROTOTYPING_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	
protected:
	UPROPERTY(meta=(BindWidget))
	UTransitionScreenWidget* TransitionScreen = nullptr;

	UPROPERTY(meta=(BindWidget))
	UButton* Button_StartGame_1 = nullptr;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button_StartGame_2 = nullptr;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button_StartGame_3 = nullptr;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button_StartGame_4 = nullptr;

	UPROPERTY(meta=(BindWidget))
	UButton* Button_QuitGame = nullptr;

private:
	ETransitionCommand Command = ETransitionCommand::None;

	int32 StartLevelIndex = 0;

	UFUNCTION()
	void TransitionFinished();

	UFUNCTION()
	void ProcessTransition();

	UFUNCTION()
	void StartLevel1() {OnStartGame(0);}
	
	UFUNCTION()
	void StartLevel2() {OnStartGame(1);}
	
	UFUNCTION()
	void StartLevel3() {OnStartGame(2);}
	
	UFUNCTION()
	void StartLevel4() {OnStartGame(3);}
	
	UFUNCTION()
	void OnStartGame(const int32 LevelIndex);

	UFUNCTION()
	void OnQuitGame();

	void StartTransition() const;

	void SetCursorVisibility(bool bIsVisible) const;
};
