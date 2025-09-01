// Copyright (c) 2025, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "GamePrimaryLayout.generated.h"

class UCommonActivatableWidgetContainerBase;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class PLUGINSSTUDYPROJECT_API UGamePrimaryLayout : public UCommonUserWidget
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintCallable)
	void RegisterWidgetStack(UPARAM(meta = (Categories = "Game.WidgetStack")) FGameplayTag Tag, UCommonActivatableWidgetContainerBase* Stack);

	UCommonActivatableWidgetContainerBase* FindWidgetStackByTag(const FGameplayTag Tag);
private:
	UPROPERTY(Transient)
	TMap<FGameplayTag, UCommonActivatableWidgetContainerBase*> RegisteredWidgetStackMap;
};
