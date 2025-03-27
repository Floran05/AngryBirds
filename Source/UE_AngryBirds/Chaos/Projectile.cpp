// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "NiagaraComponent.h"
#include "Field/FieldSystemActor.h"
#include "ChaosBuilding.h"

AProjectile::AProjectile()
	: bEnableAddImpulseOnHit(true)
	, ImpulseMultiplier(1000.f)
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(SceneRoot);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	Mesh->SetupAttachment(SceneRoot);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetNotifyRigidBodyCollision(true); // Simulation Generate Hit Events
	Mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	ProjectileFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileFX"));
	ProjectileFX->SetupAttachment(Mesh);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == nullptr || !OtherActor->IsA(AChaosBuilding::StaticClass())) return;
	if (!FieldSystemClass) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	FRotator ActorRotation = GetActorRotation();
	// AFieldSystemActor* FieldSystem = GetWorld()->SpawnActor<AFieldSystemActor>(FieldSystemClass, Hit.Location, GetActorForwardVector().Rotation(), SpawnParams);
	AFieldSystemActor* FieldSystem = GetWorld()->SpawnActor<AFieldSystemActor>(FieldSystemClass, Hit.Location, FRotator(ActorRotation.Pitch - 90.f, ActorRotation.Yaw, ActorRotation.Roll), SpawnParams);

	if (!bEnableAddImpulseOnHit) return;
	if (AChaosBuilding* Building = Cast<AChaosBuilding>(OtherActor))
	{
		Building->AddImpulseAtHitLocation(NormalImpulse * -1.f, Hit.Location);
	}
}

void AProjectile::Launch(const FVector& ImpulseVector)
{
	if (Mesh == nullptr) return;
	Mesh->AddImpulse(ImpulseVector);
}
