// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class awsTutorialTarget : TargetRules
{
	public awsTutorialTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		bValidateFormatStrings = true;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		ExtraModuleNames.Add("awsTutorial");
	}
}
