// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class UE_ANGRYBIRDS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

protected:
	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UNiagaraComponent* ProjectileFX;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFieldSystemActor> FieldSystemClass;

	UPROPERTY(EditAnywhere, Category=AngryBirds)
	bool bEnableAddImpulseOnHit;

	UPROPERTY(EditAnywhere, Category=AngryBirds)
	float ImpulseMultiplier;

protected:

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:

	UFUNCTION(BlueprintCallable)
	void Launch(const FVector& ImpulseVector);

};
