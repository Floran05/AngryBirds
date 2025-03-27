// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AShooter.generated.h"

class USceneComponent;
class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;
class USplineComponent;
class UNiagaraComponent;

UCLASS()
class UE_ANGRYBIRDS_API AAShooter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAShooter();
	UStaticMeshComponent* GetProjectile() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRearm();

	//		COMPONENTS
	// =======================
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Projectile;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	USplineComponent* ProjectilePath;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UNiagaraComponent* PathVisual;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UNiagaraComponent* ProjectileFX;
	// =======================

	UPROPERTY()
	float ProjectileRadius;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category=AngryBirds)
	float ImpulseMinMultiplier;

	UPROPERTY(EditAnywhere, Category=AngryBirds)
	float ImpulseMaxMultiplier;

	UPROPERTY(EditAnywhere, Category=AngryBirds)
	int ScrollAmount;

	float ShootPower;
	FVector ShootVector;
	bool bCanShoot;

	UPROPERTY(EditAnywhere, Category=AngryBirds)
	float ShootDelay;

	UPROPERTY(EditAnywhere)
	int BallAmount;

	UPROPERTY(VisibleAnywhere)
	int RemainingBalls;

	UPROPERTY(EditAnywhere)
	TArray<FTransform> TeleportList;
	int TeleportIndex = 0;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void Shoot();

	UFUNCTION(BlueprintImplementableEvent)
	void OnShoot();

	UFUNCTION(BlueprintCallable)
	void OnShootNotify();

	UFUNCTION(BlueprintCallable)
	int GetRemainingBalls() const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnPowerChanged(float Power);

	UFUNCTION(BlueprintCallable)
	void SetBallAmount(int Amount);

	void IncreasePower();
	void DecreasePower();

	void SetProjectileForward(FQuat quat);

	void TeleportNext();
	void TeleportPrevious();
};
