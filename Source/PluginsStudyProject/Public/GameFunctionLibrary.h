// Copyright (c) 2025, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFunctionLibrary.generated.h"

class UGameActivatableWidgetBase;

/**
 * 
 */
UCLASS()
class PLUGINSSTUDYPROJECT_API UGameFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure)
	static TSoftClassPtr<UGameActivatableWidgetBase> GetSoftWidgetClassByTag(UPARAM(meta = (Categories = "Game.Widget")) const FGameplayTag Tag);
};
