// Copyright (c) 2022. Made by Title Goose Team during LudumDare 50. All rights reserved. 

using UnrealBuildTool;
using System.Collections.Generic;

public class LudumDare50EditorTarget : TargetRules
{
	public LudumDare50EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "LudumDare50" } );
	}
}
