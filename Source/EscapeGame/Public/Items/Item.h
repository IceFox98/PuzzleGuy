// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class ESCAPEGAME_API UItem : public UObject
{
	GENERATED_BODY()
	
public:

	UItem();

	UPROPERTY(Transient)
		class UWorld* World;

	/**The display name for this item in the inventory*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText DisplayName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 Count;

	/**An optional description for the item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
		FText Description;

	/**The text for using the item. (Equip, Eat, etc)*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText UseActionText;

protected:

	virtual class UWorld* GetWorld() const override;

};
