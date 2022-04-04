// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 


#include "UserInterface/Session/PlayerStatWidget.h"

#include "Components/TextBlock.h"

void UPlayerStatWidget::SetUsername(const FString& Text, bool isPlayer)
{
	PlayerNameTextBlock->SetText(FText::FromString(Text));
	if (isPlayer) PlayerNameTextBlock->SetColorAndOpacity(PlayerColor);
}

void UPlayerStatWidget::SetScore(const FString& Text, bool isPlayer)
{
	StatBlock->SetText(FText::FromString(Text));
	if (isPlayer) StatBlock->SetColorAndOpacity(PlayerColor);
}
