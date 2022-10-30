// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickupActor.h"
#include "Items/PuzzleGuyPickupDefinition.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Components/InventoryComponent.h"
#include "Items/PuzzleGuyPickupDefinition.h"

// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CollisionVolume = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionVolume"));
	CollisionVolume->InitCapsuleSize(10.f, 10.f);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	ItemMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupActor::OnConstruction(const FTransform& Transform)
{
	if (ItemPickupDefinition && ItemPickupDefinition->DisplayMesh)
	{
		ItemMesh->SetStaticMesh(ItemPickupDefinition->DisplayMesh);
		ItemMesh->SetRelativeScale3D(ItemPickupDefinition->MeshScale);
		//ItemMesh->SetRelativeLocation(ItemPickupDefinition->WeaponMeshOffset);
	}
}

void APickupActor::OnInteract_Implementation(AController* Controller, UActorComponent* Comp)
{
	if (!Controller) return;

	APlayerCharacter* Player = Cast<APlayerCharacter>(Controller->GetPawn());

	if (Player && Player->InventoryComponent && ItemPickupDefinition)
	{
		//Player->InventoryComponent->AddItem(ItemPickupDefinition->InventoryItemDefinition);
	}
}

