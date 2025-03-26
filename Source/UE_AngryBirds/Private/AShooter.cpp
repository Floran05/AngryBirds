// Fill out your copyright notice in the Description page of Project Settings.


#include "AShooter.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AAShooter::AAShooter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(Root);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Projectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	Projectile->SetupAttachment(Root);

	ProjectilePath = CreateDefaultSubobject<USplineComponent>(TEXT("ProjectilePath"));
	ProjectilePath->SetupAttachment(Projectile);

	PathVisual = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PathVisual"));
	PathVisual->SetupAttachment(ProjectilePath);

	LaunchVelocity = 1000.0f;
	ProjectileRadius = 10.0f;
}

UStaticMeshComponent* AAShooter::GetProjectile() const
{
	return Projectile;
}

// Called when the game starts or when spawned
void AAShooter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Compute Prediction
	FPredictProjectilePathParams Params;
	Params.StartLocation = Projectile->GetComponentToWorld().GetLocation();
	Params.LaunchVelocity = Projectile->GetComponentToWorld().GetRotation().Vector() * LaunchVelocity;
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

void AAShooter::ShowProjectilePath()
{

}

void AAShooter::SetProjectileVelocity()
{

}

// Called to bind functionality to input
void AAShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

