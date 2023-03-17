using UnrealBuildTool;

public class TankGameLoading: ModuleRules

{
        public TankGameLoading(ReadOnlyTargetRules Target) : base(Target)
    {
        
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "Slate", "SlateCore", "MoviePlayer", "InputCore"});

    }
}
