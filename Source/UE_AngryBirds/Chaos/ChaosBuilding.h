// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Physics/Experimental/ChaosEventType.h"
#include "ChaosBuilding.generated.h"

UCLASS()
class UE_ANGRYBIRDS_API AChaosBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	AChaosBuilding();

protected:
	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USceneComponent* SceneRoot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UGeometryCollectionComponent* GeometryCollection;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int TotalFragments;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int DestroyedFragments;

protected:

	UFUNCTION()
	void OnChaosBreakEvent(const FChaosBreakEvent& BreakEvent);

	UFUNCTION(BlueprintImplementableEvent)
	void OnAddScore(float Score);

public:

	UFUNCTION()
	void AddImpulseAtHitLocation(const FVector& Impulse, const FVector& Location);

	float GetMaxScoreForBuilding() const;

};
