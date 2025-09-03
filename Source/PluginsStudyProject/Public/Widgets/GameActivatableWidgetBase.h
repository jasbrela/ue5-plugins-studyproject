// Copyright (c) 2025, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameActivatableWidgetBase.generated.h"

class AGamePlayerController;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class PLUGINSSTUDYPROJECT_API UGameActivatableWidgetBase : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	AGamePlayerController* GetOwningGamePlayerController();
private:
	TWeakObjectPtr<AGamePlayerController> CachedOwningPC;
};
