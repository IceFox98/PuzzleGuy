// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "EquippableItem.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UEquippableItem : public UItem
{
	GENERATED_BODY()

public:

	/**The mesh to display for this items pickup*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText HideText;

};
