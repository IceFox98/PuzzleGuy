// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzles/GridCell.h"
#include "Puzzles/MemoryGrid.h"

// Sets default values
AGridCell::AGridCell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Locked = true;
}

// Called when the game starts or when spawned
void AGridCell::BeginPlay()
{
	Super::BeginPlay();

	MatInstance = Mesh->CreateDynamicMaterialInstance(0, Mesh->GetMaterial(0));
}

// Called every frame
void AGridCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridCell::Initialize(int32 m_Position)
{
	Position = m_Position;
}

void AGridCell::ChangeColor(ECellColor SelectColor)
{
	if (!MatInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("AGridCell::ChangeColor - Material Instance is NULL!"));
		return;
	}

	FLinearColor TargetColor;

	switch (SelectColor)
	{
	case BeginFocus:
		TargetColor = InteractColor;
		break;
	case EndFocus:
		TargetColor = BaseColor;
		break;
	case Guessed:
		TargetColor = GuessedColor;
		break;
	default:
		break;
	}

	MatInstance->SetVectorParameterValue(TEXT("Color"), TargetColor);
}

void AGridCell::OnInteract_Implementation(AController* Controller, UActorComponent* Comp)
{
	OnInteractDelegate.Broadcast(Position);
}

