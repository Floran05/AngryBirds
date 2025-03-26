// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaosBuilding.h"
#include "Components/SceneComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

AChaosBuilding::AChaosBuilding()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(SceneRoot);

	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryCollection"));
	GeometryCollection->SetupAttachment(SceneRoot);
	GeometryCollection->OnChaosBreakEvent.AddDynamic(this, &AChaosBuilding::OnChaosBreakEvent);
	GeometryCollection->OnChaosCrumblingEvent.AddDynamic(this, &AChaosBuilding::OnChaosCrumblingEvent);
}

void AChaosBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

void AChaosBuilding::OnChaosBreakEvent(const FChaosBreakEvent& BreakEvent)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			INDEX_NONE,
			2.f,
			FColor::Blue,
			TEXT("ON CHAOS BREAK EVENT")
		);
	}
}

void AChaosBuilding::OnChaosCrumblingEvent(const FChaosCrumblingEvent& CrumbleEvent)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			INDEX_NONE,
			2.f,
			FColor::Red,
			TEXT("ON CHAOS CRUMBLING EVENT")
		);
	}
}