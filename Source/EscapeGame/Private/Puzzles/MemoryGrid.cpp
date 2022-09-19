// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzles/MemoryGrid.h"
#include "Puzzles/GridCell.h"
#include "Kismet/KismetArrayLibrary.h"

AMemoryGrid::AMemoryGrid()
{
	Parent = CreateDefaultSubobject<USceneComponent>(TEXT("Parent"));
	SetRootComponent(Parent);

	GenerationCellsDelay = 1.5f;
}

void AMemoryGrid::BeginPlay()
{
	Super::BeginPlay();

	GenerateGrid();
}


void AMemoryGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMemoryGrid::OnCellInteract(int32 CellPosition)
{
	CheckPosition(CellPosition);
}

void AMemoryGrid::OnCompleted()
{
	Super::OnCompleted();

	ResetCells(false);
}

void AMemoryGrid::OnLoadFromSave()
{
	Super::OnLoadFromSave();

}

void AMemoryGrid::Start()
{
	GenerateRandomSequence();
	ShowSequence(); //BP Func
}

void AMemoryGrid::ResetCells(bool bResetColor)
{
	for (int i = 0; i < Cells.Num(); i++)
	{
		// Set this due to avoid any kind of user interaction
		Cells[i]->Locked = true;
		if (bResetColor)
		{
			Cells[i]->ChangeColor(ECellColor::EndFocus);
		}
	}
}

void AMemoryGrid::GenerateGrid()
{
	if (!CellClass) return;

	for (int32 r = 0; r < GridRows; r++)
	{
		for (int32 c = 0; c < GridColumns; c++)
		{
			FVector NewPos = FVector(r * CellSpacing, c * CellSpacing, 0.f);

			AGridCell* Cell = GetWorld()->SpawnActor<AGridCell>(CellClass, NewPos, FRotator::ZeroRotator);
			Cell->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			Cell->Initialize(c + r * GridColumns);
			Cell->OnInteractDelegate.AddDynamic(this, &AMemoryGrid::OnCellInteract);

			Cells.AddUnique(Cell);
		}
	}
}

void AMemoryGrid::GenerateRandomSequence()
{
	RandomSequence.Empty();

	int32 MaxNumber = (GridRows * GridColumns) - 1;
	SequenceLength = FMath::Clamp(SequenceLength, 0, MaxNumber);

	for (int32 i = 0; i < SequenceLength; i++)
	{
		int32 RandNum = 0;

		do
		{
			RandNum = FMath::RandRange(0, MaxNumber);
		} while (RandomSequence.Contains(RandNum));

		RandomSequence.Add(RandNum);
	}
}

void AMemoryGrid::CheckPosition(int32 Position)
{
	if (RandomSequence.IsEmpty()) return;

	if (RandomSequence[0] == Position) // Guessed!
	{
		RandomSequence.RemoveAt(0);

		AGridCell* CellHit = Cells[Position];

		OnCellGuessed(CellHit); //BP Func
	}
	else // Wrong Cell!
	{
		OnWrongSequence(); //BP Func
	}
}
