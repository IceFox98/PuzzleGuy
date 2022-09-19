// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/InventoryItem.h"
#include "Characters/PlayerCharacter.h"
#include "Components/InventoryComponent.h"

// Sets default values
AInventoryItem::AInventoryItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInventoryItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInventoryItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInventoryItem::OnInteract_Implementation(class AController* Controller, UActorComponent* Comp)
{
	// Add item class to inventory comp
	APlayerCharacter* Player = Cast<APlayerCharacter>(Controller->GetPawn());

	Player->InventoryComponent->AddItem(ItemClass);
}

