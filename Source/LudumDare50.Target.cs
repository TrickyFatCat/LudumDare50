// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 

using UnrealBuildTool;
using System.Collections.Generic;

public class LudumDare50Target : TargetRules
{
	public LudumDare50Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "LudumDare50" } );
	}
}
