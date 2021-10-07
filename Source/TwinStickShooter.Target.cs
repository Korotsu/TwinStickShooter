// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TwinStickShooterTarget : TargetRules
{
	public TwinStickShooterTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("TwinStickShooter");
	}
}
