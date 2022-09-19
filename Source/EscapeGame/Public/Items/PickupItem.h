// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "PickupItem.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UPickupItem : public UItem
{
	GENERATED_BODY()
	
public:

	/**The mesh to display for this items pickup*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		class UStaticMesh* PickupMesh;

	/**The thumbnail for this item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		class UTexture2D* Thumbnail;
};
