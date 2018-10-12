// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class IGCEditorExtensionsEditor : ModuleRules
{
	public IGCEditorExtensionsEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
			new string[] 
			{ 
				"Core", 
				"CoreUObject",
                "SlateCore",
                "Slate",
                "UnrealEd",
                "LevelEditor",
                "IGCEditorExtensions"
            }
		);

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
