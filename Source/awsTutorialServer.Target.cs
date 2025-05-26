// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class awsTutorialServerTarget : TargetRules
{
	public awsTutorialServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		bValidateFormatStrings = true;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("awsTutorial");
	}
}
