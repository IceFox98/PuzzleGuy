// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/InventoryItem.h"
#include "Characters/PlayerCharacter.h"
#include "Components/InventoryComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AInventoryItem::AInventoryItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	SetRootComponent(BaseMesh);

	bIsThrowable = false;
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

void AInventoryItem::OnSelect()
{
	OnSelected.Broadcast();
	bIsSelected = true;
}

void AInventoryItem::OnUnselect()
{
	OnUnselected.Broadcast();
	bIsSelected = false;
}

void AInventoryItem::OnDrop()
{
	bIsSelected = false;

	// Play sound

	//FVector DropLocation = GetOwner()->GetActorLocation();

}

void AInventoryItem::OnUsePressed_Implementation()
{
	// Nothing
}

void AInventoryItem::OnUseReleased_Implementation()
{
	// Nothing
}

void AInventoryItem::OnInteract_Implementation(class AController* Controller, UActorComponent* Comp)
{
	// Add item class to inventory comp
	APlayerCharacter* Player = Cast<APlayerCharacter>(Controller->GetPawn());

	Player->InventoryComponent->AddItem(this);
	TriggerActors();
}

