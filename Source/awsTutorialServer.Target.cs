// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class awsTutorialServerTarget : TargetRules
{
	public awsTutorialServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		bValidateFormatStrings = true;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		ExtraModuleNames.Add("awsTutorial");
	}
}
