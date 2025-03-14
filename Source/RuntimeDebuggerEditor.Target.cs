// Copyright 2025 mellos game. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class RuntimeDebuggerEditorTarget : TargetRules
{
	public RuntimeDebuggerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("RuntimeDebugger");
	}
}
