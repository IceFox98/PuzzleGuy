// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

class UPuzzleGuyAbilitySet;

/**
 * 
 */
UCLASS(Blueprintable, Abstract, EditInlineNew)
class ESCAPEGAME_API UItem : public UObject
{
	GENERATED_BODY()
	
public:

	UItem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**The display name for this item in the inventory*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FSlateBrush ItemIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 Count;

	/**An optional description for the item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
		FText Description;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
		TArray<TObjectPtr<UPuzzleGuyAbilitySet>> AbilitySetsToGrant;

protected:

};
