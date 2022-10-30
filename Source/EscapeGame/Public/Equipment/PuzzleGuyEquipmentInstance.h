// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PuzzleGuyEquipmentInstance.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UPuzzleGuyEquipmentInstance : public UObject
{
	GENERATED_BODY()
	

public:
	UPuzzleGuyEquipmentInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void OnEquipped();
	virtual void OnUnequipped();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Equipment, meta = (DisplayName = "OnEquipped"))
		void K2_OnEquipped();

	UFUNCTION(BlueprintImplementableEvent, Category = Equipment, meta = (DisplayName = "OnUnequipped"))
		void K2_OnUnequipped();
};
