// Copyright (c) 2025, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class PLUGINSSTUDYPROJECT_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;
	virtual void BeginPlay() override;
};
