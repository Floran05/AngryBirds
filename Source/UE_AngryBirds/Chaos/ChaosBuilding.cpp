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
}

void AChaosBuilding::BeginPlay()
{
	Super::BeginPlay();
	
	TotalFragments = GeometryCollection->GetNumElements(FGeometryCollection::TransformGroup);
	DestroyedFragments = 0;
}

void AChaosBuilding::OnChaosBreakEvent(const FChaosBreakEvent& BreakEvent)
{
	DestroyedFragments++;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			INDEX_NONE,
			5.f,
			FColor::Blue,
			FString::Printf(TEXT("Destruction percentage: %.2f"), (float(DestroyedFragments) / float(TotalFragments)) * 100.0f)
		);
	}
}