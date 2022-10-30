// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/PuzzleGuyEquipmentInstance.h"

UPuzzleGuyEquipmentInstance::UPuzzleGuyEquipmentInstance(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPuzzleGuyEquipmentInstance::OnEquipped()
{
	K2_OnEquipped();
}

void UPuzzleGuyEquipmentInstance::OnUnequipped()
{
	K2_OnUnequipped();
}
