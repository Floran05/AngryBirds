// Fill out your copyright notice in the Description page of Project Settings.

#include "AShooterController.h"

#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include "GameFramework/Character.h"
#include <AShooter.h>

void AAShooterController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!InputMapping.IsNull())
			{
				InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), 0);
			}
		}
	}
}

void AAShooterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAShooterController::Look);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AAShooterController::Shoot);
	}
}

void AAShooterController::Look(const FInputActionInstance& Instance)
{
	FVector2D vector = Instance.GetValue().Get<FVector2D>();

	if (AAShooter* shooter = Cast<AAShooter>(GetPawn()))
	{
		shooter->GetProjectile()->AddWorldRotation(FRotator(vector.Y, vector.X, 0.0f));
	}

	/*GetPawn()->AddControllerYawInput(vector.X);
	GetPawn()->AddControllerPitchInput(vector.Y);*/
}

void AAShooterController::Shoot(const FInputActionInstance& Instance)
{
	bool boolean = Instance.GetValue().Get<bool>();

	if (AAShooter* shooter = Cast<AAShooter>(GetPawn()))
	{
		//shooter->GetProjectile()->
	}
}
