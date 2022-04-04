// Copyright (c) 2021 Artyom "Tricky Fat Cat" Volkov (tricky.fat.cat@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "Components/VerticalBox.h"
#include "Interfaces/IHttpRequest.h"
#include "UserInterface/Session/BaseSessionScreenWidget.h"
#include "GameOverScreenWidget.generated.h"

class UButton;
class UTransitionScreenWidget;

/**
 * 
 */

UCLASS()
class TRICKYPROTOTYPING_API UGameOverScreenWidget : public UBaseSessionScreenWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta=(BindWidget))
	UButton* Button_NextLevel = nullptr;
	
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* Stats = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;
	
private:
	virtual void OnTransitionScreenShowed() override;
	
	UFUNCTION()
	void OnNextLevelPressed();

	void OpenNextLevel() const;

	UFUNCTION(BlueprintPure, Category="UI")
	float GetFinalTime();

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);
	UFUNCTION(BlueprintCallable)
	void ShowStat();

	float Time = 0.0f;
	
};
