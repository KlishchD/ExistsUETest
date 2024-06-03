// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using UnrealBuildTool.Rules;

public class ExistsUETest : ModuleRules
{
	public ExistsUETest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
			{
				"Core", 
				"CoreUObject", 
				"Engine", 
				"InputCore", 
				"EnhancedInput", 
				"Slate", 
				"UMG", 
				"OnlineSubsystem", 
				"OnlineSubsystemUtils", 
				"Json", 
				"JsonUtilities",
                "DeveloperSettings"
            }
		);
	}
}
