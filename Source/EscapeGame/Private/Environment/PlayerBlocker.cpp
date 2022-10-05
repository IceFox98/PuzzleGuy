// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/PlayerBlocker.h"
#include "Components/BoxComponent.h"
#include "PuzzleGuyUtils.h"

// Sets default values
APlayerBlocker::APlayerBlocker()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetRelativeScale3D(FVector(2.f, 1.f, 3.f));
	Mesh->SetRelativeLocation(FVector(0.f, 0.f, -300.f));

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(Root);
	Box->SetRelativeLocation(FVector(0.f, 200.f, 0.f));
	Box->SetBoxExtent(FVector(90.f, 150.f, 150.f));

	Angle = 0.f;
	MaxAngle = 90.f;
	AnglePerSeconds = 250.f;
	bOverlapping = false;
	MovementAmount = FVector(0.f, 0.f, 300.f);
	InitialMeshOffset = FVector::ZeroVector;
}

// Called when the game starts or when spawned
void APlayerBlocker::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &APlayerBlocker::OnBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &APlayerBlocker::OnEndOverlap);

	InitialMeshOffset = Mesh->GetRelativeLocation();
}

// Called every frame
void APlayerBlocker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Mesh->GetStaticMesh())
	{
		SCREEN_LOG(1.f, FColor::Red, "APlayerBlocker::Tick - Mesh is NULL!");
		return;
	}

	bool bOverlappingConditions = (Angle >= 0 && (Angle < MaxAngle) && bOverlapping);
	bool bNotOverlappingConditions = (Angle > 0 && AnglePerSeconds < 0 && !bOverlapping);

	if (bOverlappingConditions || bNotOverlappingConditions)
	{
		MoveBlockTick(DeltaTime);
	}
}

void APlayerBlocker::MoveBlockTick(float DeltaTime)
{
	Angle = FMath::Clamp(Angle + (AnglePerSeconds * DeltaTime), 0.f, MaxAngle);

	// Simulate up & down movement using Sin function
	FVector NewLocation = FMath::Sin(FMath::DegreesToRadians(Angle)) * MovementAmount;
	NewLocation += InitialMeshOffset;

	Mesh->SetRelativeLocation(NewLocation);
}

void APlayerBlocker::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bOverlapping = true;

	if (AnglePerSeconds < 0)
	{
		// Change movement direction, only if it's already negative
		AnglePerSeconds = -AnglePerSeconds;
	}
}

void APlayerBlocker::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bOverlapping = false;

	// Change movement direction
	AnglePerSeconds = -AnglePerSeconds;
}

