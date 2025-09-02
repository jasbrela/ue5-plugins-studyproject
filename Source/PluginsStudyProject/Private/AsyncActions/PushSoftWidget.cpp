// Copyright (c) 2025, Jasbrela. All rights reserved.


#include "AsyncActions/PushSoftWidget.h"

#include "GameUISubsystem.h"

UPushSoftWidget* UPushSoftWidget::PushSoftWidget(const UObject* WorldContextObject,
                                                 APlayerController* OwningPlayerController,
                                                 TSoftClassPtr<UGameActivatableWidgetBase> SoftWidgetClass,
                                                 UPARAM(meta = (Categories = "Game.WidgetStack"))
                                                 FGameplayTag Tag, bool bFocusOnNewlyPushedWidget)
{
	checkf(!SoftWidgetClass.IsNull(), TEXT("PushSoftWidget was passed a null soft widget class"));

	if (GEngine)
	{
		if (UWorld* World = GEngine->
			GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			UPushSoftWidget* Node = NewObject<UPushSoftWidget>();

			Node->CachedWorld = World;
			Node->CachedWidgetClass = SoftWidgetClass;
			Node->CachedPlayerController = OwningPlayerController;
			Node->Tag = Tag;
			Node->bCachedFocusOnNewlyPushedWidget = bFocusOnNewlyPushedWidget;

			Node->RegisterWithGameInstance(World);

			return Node;
		}
	}

	return nullptr;
}

void UPushSoftWidget::Activate()
{
	Super::Activate();
	UGameUISubsystem* Subsystem = UGameUISubsystem::Get(CachedWorld.Get());

	Subsystem->PushSoftWidgetToStackAsync(
		Tag, CachedWidgetClass,
		[this](EAsyncPushWidgetState State, UGameActivatableWidgetBase* PushedWidget)
		{
			switch (State)
			{
			case EAsyncPushWidgetState::OnCreatedBeforePush:
				PushedWidget->SetOwningPlayer(CachedPlayerController.Get());
				OnWidgetCreatedBeforePush.Broadcast(PushedWidget);
				break;
			case EAsyncPushWidgetState::AfterPush:
				OnWidgetPushed.Broadcast(PushedWidget);

				if (bCachedFocusOnNewlyPushedWidget)
				{
					if (UWidget* Widget = PushedWidget->GetDesiredFocusTarget())
					{
						Widget->SetFocus();
					}

					SetReadyToDestroy();
				}
				break;
			default:
				break;
			}
		});
}
