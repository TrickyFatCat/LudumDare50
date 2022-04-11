// Copyright (c) 2021 Artyom "Tricky Fat Cat" Volkov (tricky.fat.cat@gmail.com)


#include "Core/TrickyGameInstance.h"
#include "Kismet/GameplayStatics.h"

FName UTrickyGameInstance::GetStartLevelName() const
{
	if (LevelNames.Num() == 0) return NAME_None;

	return LevelNames[FMath::RandRange(0, LevelNames.Num() - 1)];
}

FName UTrickyGameInstance::GetNextLevelName() const
{
	FName NextLevelName = GetStartLevelName();
	const FName CurrentLevelName = FName(UGameplayStatics::GetCurrentLevelName(this));

	if (CurrentLevelName.IsNone() || !LevelNames.Contains(CurrentLevelName))
	{
		NextLevelName = MainMenuLevelName;
		return NextLevelName;
	}

	// for (int32 i = 0; i < LevelNames.Num(); ++i)
	// {
	// 	if (LevelNames[i] != CurrentLevelName) continue;
	//
	// 	if (i + 1 >= LevelNames.Num())
	// 	{
	// 		NextLevelName = MainMenuLevelName;
	// 		break;
	// 	}
	//
	// 	NextLevelName = LevelNames[i + 1];
	// 	break;
	// }

	return NextLevelName;
}

FName UTrickyGameInstance::GetLevelName(const int32 LevelIndex) const
{
	if (LevelIndex < 0 || LevelIndex >= LevelNames.Num()) return NAME_None;

	return LevelNames[LevelIndex];
}
