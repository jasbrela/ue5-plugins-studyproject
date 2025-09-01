// Copyright (c) 2025, Jasbrela. All rights reserved.


#include "Widgets/GamePrimaryLayout.h"

void UGamePrimaryLayout::RegisterWidgetStack(UPARAM(meta = (Categories = "Game.WidgetStack")) FGameplayTag Tag, UCommonActivatableWidgetContainerBase* Stack)
{
	if (IsDesignTime())
	{
		return;
	}
	
	if (RegisteredWidgetStackMap.Contains(Tag))
	{
		return;
	}

	RegisteredWidgetStackMap.Add(Tag, Stack);
}

UCommonActivatableWidgetContainerBase* UGamePrimaryLayout::FindWidgetStackByTag(const FGameplayTag Tag)
{
	checkf(RegisteredWidgetStackMap.Contains(Tag), TEXT("Cannot find widget stack by the tag %s"), *Tag.ToString());

	return RegisteredWidgetStackMap.FindRef(Tag);
}
