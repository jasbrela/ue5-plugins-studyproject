// Copyright (c) 2025, Jasbrela. All rights reserved.


#include "PluginsStudyProject/Public/GameCharacter.h"

#include "EnhancedInputComponent.h"

AGameCharacter::AGameCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameCharacter::Move(const FInputActionValue& Value)
{
	if (!bCanMoveAndLook)
	{
		return;
	}

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AGameCharacter::Look(const FInputActionValue& Value)
{
	if (!bCanMoveAndLook) return;

	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookAxisVector.X * SensX);
		AddControllerPitchInput(LookAxisVector.Y * SensY);
	}
}

void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	}
}

