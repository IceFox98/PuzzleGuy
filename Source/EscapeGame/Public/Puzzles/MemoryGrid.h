// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzles/PuzzleBase.h"
#include "MemoryGrid.generated.h"

/**
 *
 */
UCLASS()
class ESCAPEGAME_API AMemoryGrid : public APuzzleBase
{
	GENERATED_BODY()

public:

	AMemoryGrid();

protected:

	UPROPERTY(VisibleAnywhere)
		USceneComponent* Parent;

	UPROPERTY(EditAnywhere, Category = "Grid")
		TSubclassOf<class AGridCell> CellClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
		int32 GridRows;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
		int32 GridColumns;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
		float CellSpacing;

	// How many random number will be generated
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
		int32 SequenceLength;

	// How much time must pass between a cell and others, during sequence show up
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
		float GenerationCellsDelay;

	UPROPERTY(BlueprintReadOnly)
		TArray<class AGridCell*> Cells;

	UPROPERTY(BlueprintReadOnly)
		TArray<int32> RandomSequence;

private:


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnCellInteract(int32 CellPosition);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnCompleted() override;

	virtual void OnLoadFromSave() override;

	void GenerateGrid();

	UFUNCTION(BlueprintCallable)
		void Start();

	UFUNCTION(BlueprintCallable)
		void ResetCells(bool bResetColor);

	void GenerateRandomSequence();

	void CheckPosition(int32 Position);

	UFUNCTION(BlueprintImplementableEvent)
		void ShowSequence();

	UFUNCTION(BlueprintImplementableEvent)
		void OnCellGuessed(class AGridCell* GuessedCell);

	UFUNCTION(BlueprintImplementableEvent)
		void OnWrongSequence();

};
