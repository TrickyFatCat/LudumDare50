// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 


#include "UserInterface/Session/PlayerStatWidget.h"

#include "Components/TextBlock.h"

void UPlayerStatWidget::SetUsername(const FString& Text)
{
	PlayerNameTextBlock->SetText(FText::FromString(Text));
}

void UPlayerStatWidget::SetScore(const FString& Text)
{
	StatBlock->SetText(FText::FromString(Text));
}
