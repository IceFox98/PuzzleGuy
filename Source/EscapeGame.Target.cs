// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class EscapeGameTarget : TargetRules
{
	public EscapeGameTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		
		if (Configuration == UnrealTargetConfiguration.Shipping)
        {
            //BuildEnvironment = TargetBuildEnvironment.Unique;
            //bUseChecksInShipping = true;
            bUseLoggingInShipping = true;
        }

		
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "EscapeGame" } );
	}
}
