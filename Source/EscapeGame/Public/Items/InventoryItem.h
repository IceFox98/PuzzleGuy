// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactives/Interactable.h"
#include "InventoryItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSelected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnselected);


UCLASS()
class ESCAPEGAME_API AInventoryItem : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInventoryItem();

	FOnSelected OnSelected;
	FOnUnselected OnUnselected;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
		class UStaticMeshComponent* BaseMesh;

protected:

	bool bIsSelected;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
		bool bIsThrowable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	//	TSubclassOf<class UItem> ItemClass;


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item")
		FORCEINLINE bool IsSelected() { return bIsSelected; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item")
		FORCEINLINE bool IsThrowable() { return bIsThrowable; }

	/** Called when item is selected from inventory */
	virtual void OnSelect();

	/** Called when item is deselected from inventory */
	virtual void OnUnselect();

	/** Called when item is picked up from the world */
	virtual void OnPickup() PURE_VIRTUAL(AInventoryItem::OnPickup, ;);

	/** Called when item is dropped into the world */
	virtual void OnDrop();

	/** Called when item is pressed after being selected from inventory */
	UFUNCTION(BlueprintNativeEvent)
		void OnUsePressed();

	/** Called when item is released after being selected from inventory */
	UFUNCTION(BlueprintNativeEvent)
		void OnUseReleased();

	virtual void OnInteract_Implementation(class AController* Controller, UActorComponent* Comp) override;

};
