// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "EquippableItem.generated.h"

class UPuzzleGuyEquipmentInstance;

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UEquippableItem : public UItem
{
	GENERATED_BODY()

public:

	/**The mesh to display for this items pickup*/
	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
		TSubclassOf<UPuzzleGuyEquipmentInstance> InstanceType;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
		//TSubclassOf<FLyraEquipmentActorToSpawn> ActorsToSpawn;
		TSubclassOf<AActor> ActorsToSpawn;

};
