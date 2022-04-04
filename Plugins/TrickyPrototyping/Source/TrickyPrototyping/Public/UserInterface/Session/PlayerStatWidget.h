// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatWidget.generated.h"

class UTextBlock;
UCLASS()
class TRICKYPROTOTYPING_API UPlayerStatWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetUsername (const FString& Text);
	void SetScore (const FString& Text);
	
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* PlayerNameTextBlock;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* StatBlock;
};
