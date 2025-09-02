// Copyright (c) 2025, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"
#include "GameUIDeveloperSettings.generated.h"
/**
 * 
 */

class UGameActivatableWidgetBase;

// The defaultconfig specifier within the UCLASS macro in Unreal Engine indicates that configuration settings for instances of that class will only be saved to the default INI files, and never to local INI files.
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Game UI Settings"))
class PLUGINSSTUDYPROJECT_API UGameUIDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(Config, EditAnywhere, Category = "Widget References", meta = (ForceInlineRow, Categories="Game.Widget"))
	TMap<FGameplayTag, TSoftClassPtr<UGameActivatableWidgetBase>> WidgetMap;
};
