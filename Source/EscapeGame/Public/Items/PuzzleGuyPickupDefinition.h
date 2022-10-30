// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PuzzleGuyPickupDefinition.generated.h"

class UItem;
//class UNiagaraSystem;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ESCAPEGAME_API UPuzzleGuyPickupDefinition : public UDataAsset
{
	GENERATED_BODY()
	

public:

	//Defines the pickup's actors to spawn, abilities to grant, and tags to add
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PuzzleGuy|Pickup|Item")
		TSubclassOf<UItem> InventoryItemDefinition;

	//Visual representation of the pickup
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PuzzleGuy|Pickup|Mesh")
		UStaticMesh* DisplayMesh;

	//Sets the height of the display mesh above the Weapon spawner
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PuzzleGuy|Pickup|Mesh")
		FVector MeshScale = FVector(1.0f, 1.0f, 1.0f);

	//Sound to play when picked up
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PuzzleGuy|Pickup")
		USoundBase* PickedUpSound;


	////Particle FX to play when picked up
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PuzzleGuy|Pickup")
	//	UNiagaraSystem* PickedUpEffect;

};
