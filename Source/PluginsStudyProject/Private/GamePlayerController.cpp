// Copyright (c) 2025, Jasbrela. All rights reserved.


#include "PluginsStudyProject/Public/GamePlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "GameUISubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void AGamePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	// SET UP PRIMARY LAYOUT
	if (UWorld* World = GetWorld(); IsValid(PrimaryLayoutClass) && World)
	{
		UGamePrimaryLayout* Widget = CreateWidget<UGamePrimaryLayout>(World, PrimaryLayoutClass);
		Widget->AddToViewport();

		UGameUISubsystem* UISubsystem = GetGameInstance()->GetSubsystem<UGameUISubsystem>();
		UISubsystem->RegisterCreatedPrimaryLayoutWidget(Widget);

		/*
		auto tag = UGameplayTagsManager::Get().RequestGameplayTag("Game.WidgetStack.Menu");
		UISubsystem->PushSoftWidgetToStackAsync(tag, DebugActivatableWidget, [](EAsyncPushWidgetState State, UGameActivatableWidgetBase* Widget)
		{
			LOG("DEBUG!!!!!!!");
		});*/
	}

	// SET UP CAMERA
	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(), FName("Default"), FoundCameras);

	if (FoundCameras.IsEmpty())
	{
		return;
	}

	SetViewTarget(FoundCameras[0]);
}

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}
