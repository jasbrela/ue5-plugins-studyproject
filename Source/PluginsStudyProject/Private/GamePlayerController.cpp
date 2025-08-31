// Copyright (c) 2025, Jasbrela. All rights reserved.


#include "PluginsStudyProject/Public/GamePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void AGamePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

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
