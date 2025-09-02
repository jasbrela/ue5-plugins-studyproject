// Copyright (c) 2025, Jasbrela. All rights reserved.


#include "GameFunctionLibrary.h"
#include "DevSettings/GameUIDeveloperSettings.h"

TSoftClassPtr<UGameActivatableWidgetBase> UGameFunctionLibrary::GetSoftWidgetClassByTag(UPARAM(meta = (Categories = "Game.Widget")) const FGameplayTag Tag)
{
	const UGameUIDeveloperSettings* DevSettings = GetDefault<UGameUIDeveloperSettings>();

	checkf(DevSettings->WidgetMap.Contains(Tag), TEXT("Could not find widget under the tag %s"), *Tag.ToString());

	return DevSettings->WidgetMap.FindRef(Tag);
}
