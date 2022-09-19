// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class ESCAPEGAME_API IInteractable
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void OnBeginFocus(class AController* Controller, class UActorComponent* Comp);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void OnEndFocus(class AController* Controller);

	UFUNCTION(BlueprintImplementableEvent)
		bool IsComponentInteractive(class UActorComponent* Comp);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnInteract(class AController* Controller, class UActorComponent* Comp);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		FString GetInteractionText(class UActorComponent* Comp);
};
