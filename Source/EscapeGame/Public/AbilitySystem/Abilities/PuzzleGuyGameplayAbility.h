// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Characters/PlayerCharacter.h"
#include "PuzzleGuyGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UPuzzleGuyGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPuzzleGuyGameplayAbility();

	// Abilities will activate when input is pressed
	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "Abilities")
		EPuzzleGuyAbilityInputID AbilityInputID {
		EPuzzleGuyAbilityInputID::None
	};
};
