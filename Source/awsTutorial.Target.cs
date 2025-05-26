// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class awsTutorialTarget : TargetRules
{
	public awsTutorialTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		bValidateFormatStrings = true;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("awsTutorial");
	}
}
