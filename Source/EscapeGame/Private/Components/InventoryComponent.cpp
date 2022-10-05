// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "Items/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SelectedIndex = -1;
	SelectedItem = nullptr;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

AInventoryItem* UInventoryComponent::AddItem(AInventoryItem* NewItem)
{
	if (!NewItem) return nullptr;

	Items.Add(NewItem);

	// Hide instead of destroy to keep actor data
	NewItem->SetActorHiddenInGame(true);
	NewItem->BaseMesh->SetSimulatePhysics(false);
	NewItem->SetActorEnableCollision(false);
	NewItem->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	NewItem->SetOwner(GetOwner());
	NewItem->SetActorRelativeLocation(FVector::ZeroVector);
	NewItem->SetActorRelativeRotation(FRotator::ZeroRotator);

	//if (Items.Num() == 1)
	//{
	//	// If we didn't have any items, select the one just added
	//	SelectItem(0);
	//}

	// Select always last collected item
	SelectItem(Items.Num() - 1);

	return NewItem;
}

void UInventoryComponent::RemoveItem(AInventoryItem* ItemToRemove)
{
	if (!ItemToRemove) return;

	Items.Remove(ItemToRemove);
	PrevItem();
}

void UInventoryComponent::SelectItem(int32 Index)
{
	if (SelectedIndex == Index) return;

	// Unselect current item and hide it
	if (SelectedItem)
	{
		SelectedItem->SetActorHiddenInGame(true);
		SelectedItem->OnUnselect();
	}

	// Disable collisions?

	// Select new item
	SelectedIndex = Index;
	SelectedItem = SelectedIndex >= 0 ? Items[SelectedIndex] : nullptr;

	if (SelectedItem)
	{
		SelectedItem->OnSelect();
	}
}

void UInventoryComponent::NextItem()
{
	if (Items.IsEmpty())
	{
		SelectItem(-1);
		return;
	}

	// Select next item
	int32 NewIndex = (SelectedIndex + 1) % Items.Num();
	SelectItem(NewIndex);
}

void UInventoryComponent::PrevItem()
{
	if (Items.IsEmpty())
	{
		SelectItem(-1);
		return;
	}

	// Select prev item
	int32 NewIndex = (SelectedIndex - 1 + Items.Num()) % Items.Num();
	SelectItem(NewIndex);
}

AInventoryItem* UInventoryComponent::DropSelectedItem()
{
	if (SelectedItem)
	{
		AInventoryItem* ItemToDrop = SelectedItem;

		RemoveItem(ItemToDrop);

		ItemToDrop->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		ItemToDrop->SetActorHiddenInGame(false);
		ItemToDrop->SetActorEnableCollision(true);
		ItemToDrop->BaseMesh->SetSimulatePhysics(true);
		//ItemToDrop->SetOwner(nullptr);
		ItemToDrop->OnDrop();

		return ItemToDrop;
	}

	return nullptr;
}
