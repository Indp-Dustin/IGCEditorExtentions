// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class IGCEditorExtensionsTarget : TargetRules
{
	public IGCEditorExtensionsTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "IGCEditorExtensions" } );
	}
}
