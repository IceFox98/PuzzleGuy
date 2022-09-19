// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"

#define LOCTEXT_NAMESPACE "Item"

UItem::UItem()
{
	DisplayName = LOCTEXT("ItemName", "Item");
	UseActionText = LOCTEXT("ItemUseActionText", "Use");
}

class UWorld* UItem::GetWorld() const
{
	return World;
}
