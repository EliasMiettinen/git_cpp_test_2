// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class git_test_cpp_2 : ModuleRules
{
	public git_test_cpp_2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
