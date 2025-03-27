// Fill out your copyright notice in the Description page of Project Settings.


#include "AShooter.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Chaos/Projectile.h"


// Sets default values
AAShooter::AAShooter()
	: ImpulseMinMultiplier(200000.f)
	, ImpulseMaxMultiplier(500000.f)
	, ScrollAmount(20)
	, ShootPower(0.5f)
	, bCanShoot(true)
	, ShootDelay(1.5f)
	, BallAmount(10)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMesh->SetupAttachment(Root);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(SkeletalMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Projectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	Projectile->SetupAttachment(SkeletalMesh, FName("RightHand"));

	ProjectilePath = CreateDefaultSubobject<USplineComponent>(TEXT("ProjectilePath"));
	ProjectilePath->SetupAttachment(Projectile);

	PathVisual = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PathVisual"));
	PathVisual->SetupAttachment(ProjectilePath);

	ProjectileFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileFX"));
	ProjectileFX->SetupAttachment(Projectile);

	RemainingBalls = BallAmount;
}

UStaticMeshComponent* AAShooter::GetProjectile() const
{
	return Projectile;
}

// Called when the game starts or when spawned
void AAShooter::BeginPlay()
{
	Super::BeginPlay();

	ProjectileRadius = 100.f * 0.5f * Projectile->GetRelativeScale3D().X;
}

// Called every frame
void AAShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Compute Prediction
	FPredictProjectilePathParams Params;
	Params.StartLocation = Projectile->GetComponentToWorld().GetLocation();
	Params.LaunchVelocity = Projectile->GetForwardVector() * ((ImpulseMaxMultiplier - ImpulseMinMultiplier) * ShootPower + ImpulseMinMultiplier) / 1000.f;
	Params.ProjectileRadius = ProjectileRadius;
	FPredictProjectilePathResult Result;
	bool bHit = UGameplayStatics::PredictProjectilePath(GetWorld(), Params, Result);

	//Make Spline
	TArray<FVector> PointsLocation;

	for (auto PathPoint : Result.PathData)
	{
		PointsLocation.Add(PathPoint.Location);
	}

	ProjectilePath->SetSplinePoints(PointsLocation, ESplineCoordinateSpace::World);
}

void AAShooter::OnRearm()
{
	bCanShoot = true;
	Projectile->SetVisibility(true, true);
}

void AAShooter::OnShootNotify()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Projectile->GetComponentLocation(), Projectile->GetRelativeRotation(), SpawnParameters);
	SpawnedProjectile->Launch(ShootVector * ((ImpulseMaxMultiplier - ImpulseMinMultiplier) * ShootPower + ImpulseMinMultiplier));

	Projectile->SetVisibility(false, true);
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AAShooter::OnRearm, ShootDelay, false);
}

int AAShooter::GetRemainingBalls() const
{
	return RemainingBalls;
}

// Called to bind functionality to input
void AAShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAShooter::Shoot()
{
	if (!ProjectileClass || !bCanShoot || RemainingBalls <= 0) return;

	bCanShoot = false;
	RemainingBalls--;
	ShootVector = Projectile->GetForwardVector();
	ProjectilePath->SetVisibility(false, true);
	OnShoot();
}

void AAShooter::IncreasePower()
{
	ShootPower += (1.f / ScrollAmount);
	if (ShootPower > 1.f) ShootPower = 1.f;

	OnPowerChanged(ShootPower);
}

void AAShooter::DecreasePower()
{
	ShootPower -= (1.f / ScrollAmount);
	if (ShootPower < 0.f) ShootPower = 0.f;

	OnPowerChanged(ShootPower);
}

