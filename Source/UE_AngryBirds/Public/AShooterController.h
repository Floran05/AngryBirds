// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "AShooterController.generated.h"

UCLASS()
class UE_ANGRYBIRDS_API AAShooterController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void Look(const FInputActionInstance& Instance);
	void Shoot(const FInputActionInstance& Instance);

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditAnywhere)
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere)
	UInputAction* ShootAction;
};
