// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "Items/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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

	SelectedItem = NewItem;

	return NewItem;
}
