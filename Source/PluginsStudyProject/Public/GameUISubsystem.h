// Copyright (c) 2025, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Widgets/GameActivatableWidgetBase.h"
#include "GameUISubsystem.generated.h"

class UGameActivatableWidgetBase;
struct FGameplayTag;
class UGamePrimaryLayout;
enum class EAsyncPushWidgetState : uint8
{
	OnCreatedBeforePush,
	AfterPush,
};
/**
 * 
 */
UCLASS()
class PLUGINSSTUDYPROJECT_API UGameUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	static UGameUISubsystem* Get(const UObject* WorldContextObject);

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	UFUNCTION(BlueprintCallable)
	void RegisterCreatedPrimaryLayoutWidget(UGamePrimaryLayout* Widget);

	void PushSoftWidgetToStackAsync(const FGameplayTag& Tag, TSoftClassPtr<UGameActivatableWidgetBase> WidgetClass, TFunction<void(EAsyncPushWidgetState, UGameActivatableWidgetBase*)> AsyncPushStateCallback);

private:
	UPROPERTY(Transient)
	UGamePrimaryLayout* PrimaryLayout;
	
};
