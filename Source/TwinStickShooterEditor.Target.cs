// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TwinStickShooterEditorTarget : TargetRules
{
	public TwinStickShooterEditorTarget(TargetInfo Target) : base (Target)
	{
		Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.Add("TwinStickShooter");
	}
}
