// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactives/Interactable.h"
#include "InventoryItem.generated.h"

UCLASS()
class ESCAPEGAME_API AInventoryItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
		TSubclassOf<class UItem> ItemClass;

	virtual void OnInteract_Implementation(class AController* Controller, UActorComponent* Comp) override;

};
