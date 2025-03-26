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
	GeometryCollection->SetSimulatePhysics(true);
	GeometryCollection->SetNotifyRigidBodyCollision(true);
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
	OnAddScore(GeometryCollection->GetMass() * (1.f / TotalFragments));
}

void AChaosBuilding::AddImpulseAtHitLocation(const FVector& Impulse, const FVector& Location)
{
	GeometryCollection->AddImpulseAtLocation(Impulse, Location);
}
