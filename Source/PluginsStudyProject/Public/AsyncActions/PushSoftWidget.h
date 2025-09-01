// Copyright (c) 2025, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameplayTagContainer.h"
#include "PushSoftWidget.generated.h"

class UGameActivatableWidgetBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushSoftWidgetDelegate, UGameActivatableWidgetBase*, PushedWidget);
/**
 * 
 */
UCLASS()
class PLUGINSSTUDYPROJECT_API UPushSoftWidget : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,
		meta = (WorldContext = "WorldContextObject", HidePin="WorldContextObject", BlueprintInternalUseOnly="true",
			DisplayName="Push Soft Widget To Widget Stack"))
	static UPushSoftWidget* PushSoftWidget(const UObject* WorldContextObject, APlayerController* OwningPlayerController,
	                                       TSoftClassPtr<UGameActivatableWidgetBase> SoftWidgetClass,
	                                       UPARAM(meta = (Categories = "Game.WidgetStack"))
	                                       FGameplayTag Tag, bool bFocusOnNewlyPushedWidget = true);

	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate OnWidgetCreatedBeforePush;
	
	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate OnWidgetPushed;

private:
	TWeakObjectPtr<UWorld> CachedWorld;
	TWeakObjectPtr<APlayerController> CachedPlayerController;
	TSoftClassPtr<UGameActivatableWidgetBase> CachedWidgetClass;
	FGameplayTag Tag;
	bool bCachedFocusOnNewlyPushedWidget = false;
};
