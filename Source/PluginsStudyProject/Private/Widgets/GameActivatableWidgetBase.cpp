// Copyright (c) 2025, Jasbrela. All rights reserved.


#include "Widgets/GameActivatableWidgetBase.h"
#include "GamePlayerController.h"

AGamePlayerController* UGameActivatableWidgetBase::GetOwningGamePlayerController()
{
	if (!CachedOwningPC.IsValid())
	{
		CachedOwningPC = GetOwningPlayer<AGamePlayerController>();
	}
	
	return CachedOwningPC.IsValid() ? CachedOwningPC.Get() : nullptr;
}
