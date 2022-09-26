// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/InventoryItem.h"
#include "InventoryComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ESCAPEGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<AInventoryItem*> Items;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AInventoryItem* SelectedItem;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		AInventoryItem* AddItem(AInventoryItem* NewItem);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE AInventoryItem* GetSelectedItem() const { return SelectedItem; }

};
