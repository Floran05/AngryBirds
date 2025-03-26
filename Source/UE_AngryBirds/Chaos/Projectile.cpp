// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "Field/FieldSystemActor.h"
#include "ChaosBuilding.h"

AProjectile::AProjectile()
	: Impulse(FVector(0.f))
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(SceneRoot);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	Mesh->SetupAttachment(SceneRoot);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetNotifyRigidBodyCollision(true); // Simulation Generate Hit Events
	Mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	Mesh->AddImpulse(Impulse);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == nullptr || !OtherActor->IsA(AChaosBuilding::StaticClass())) return;
	if (!FieldSystemClass) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	AFieldSystemActor* FieldSystem = GetWorld()->SpawnActor<AFieldSystemActor>(FieldSystemClass, Hit.Location, GetActorForwardVector().Rotation(), SpawnParams);
}
