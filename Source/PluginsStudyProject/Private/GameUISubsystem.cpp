// Copyright (c) 2025, Jasbrela. All rights reserved.


#include "GameUISubsystem.h"

#include "ConsolidateWindow.h"
#include "DebugMacros.h"
#include "Components/WidgetInteractionComponent.h"
#include "Engine/AssetManager.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/GameActivatableWidgetBase.h"
#include "Widgets/GamePrimaryLayout.h"

UGameUISubsystem* UGameUISubsystem::Get(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);
		return UGameInstance::GetSubsystem<UGameUISubsystem>(World->GetGameInstance());
	}
	
	return nullptr;
}

bool UGameUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	// Ensure the subsystem is not unnecessarily created on server instances.
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> FoundClasses;
		GetDerivedClasses(GetClass(),FoundClasses);
		// This check ensures that only the most derived version of the subsystem actually gets instantiated. Otherwise, you could end up with duplicate subsystems (base + derived).
		// This pattern is common for subsystems that are meant to be abstract bases (like UI or input systems), where you want only the most specialized implementation to be used.

		return FoundClasses.IsEmpty();
	}
	
	return false;
}

void UGameUISubsystem::RegisterCreatedPrimaryLayoutWidget(UGamePrimaryLayout* Widget)
{
	check(Widget);
	PrimaryLayout = Widget;

	LOG("PrimaryWidget stored");
}

void UGameUISubsystem::PushSoftWidgetToStackAsync(const FGameplayTag& Tag,
	TSoftClassPtr<UGameActivatableWidgetBase> WidgetClass,
	TFunction<void(EAsyncPushWidgetState,
	UGameActivatableWidgetBase*)> AsyncPushStateCallback)
{
	check(!WidgetClass.IsNull());
	
	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		WidgetClass.ToSoftObjectPath(), FStreamableDelegate::CreateLambda(
		[WidgetClass, this, Tag, AsyncPushStateCallback]()
		{
			UClass* LoadedClass = WidgetClass.Get();
			check(LoadedClass && PrimaryLayout);

			UCommonActivatableWidgetContainerBase* Stack = PrimaryLayout->FindWidgetStackByTag(Tag);
			UGameActivatableWidgetBase* Widget = Stack->AddWidget<UGameActivatableWidgetBase>(
				LoadedClass,
				[AsyncPushStateCallback](UGameActivatableWidgetBase& WidgetInstance)
				{
					AsyncPushStateCallback(EAsyncPushWidgetState::OnCreatedBeforePush, &WidgetInstance);
				}
			);
			AsyncPushStateCallback(EAsyncPushWidgetState::AfterPush, Widget);
		})
	);
}
