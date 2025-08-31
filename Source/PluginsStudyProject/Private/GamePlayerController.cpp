// Copyright (c) 2025, Jasbrela. All rights reserved.


#include "PluginsStudyProject/Public/GamePlayerController.h"
#include "EnhancedInputSubsystems.h"

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}
