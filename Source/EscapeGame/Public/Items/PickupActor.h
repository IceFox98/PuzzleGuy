// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactives/Interactable.h"
#include "PickupActor.generated.h"

class UPuzzleGuyPickupDefinition;
class UCapsuleComponent;

UCLASS()
class ESCAPEGAME_API APickupActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupActor();

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PuzzleGuy|ItemPickup")
		UCapsuleComponent* CollisionVolume;

	UPROPERTY(BlueprintReadOnly, Category = "PuzzleGuy|ItemPickup")
		UStaticMeshComponent* ItemMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnConstruction(const FTransform& Transform) override;

	virtual void OnInteract_Implementation(class AController* Controller, UActorComponent* Comp) override;

protected:
	//Data asset used to configure a Weapon Spawner
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "PuzzleGuy|ItemPickup")
		UPuzzleGuyPickupDefinition* ItemPickupDefinition;

};
