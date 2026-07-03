// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ValidateProject : ModuleRules
{
	public ValidateProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// 把模块根目录加入 include 搜索路径，使 "Core/xxx.h"、"Character/xxx.h" 这类
		// 带子目录前缀的包含路径可被正确解析（否则报 C1083 无法打开包括文件）。
		PublicIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
