// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "PuzzleGuyAbilitySet.generated.h"

class UPuzzleGuyGameplayAbility;

/**
 * FPuzzleGuyAbilitySet_GameplayAbility
 *
 *	Data used by the ability set to grant gameplay abilities.
 */
USTRUCT(BlueprintType)
struct FPuzzleGuyAbilitySet_GameplayAbility
{
	GENERATED_BODY()

public:

	// Gameplay ability to grant.
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UPuzzleGuyGameplayAbility> Ability = nullptr;

	// Level of ability to grant.
	UPROPERTY(EditDefaultsOnly)
		int32 AbilityLevel = 1;

	// Tag used to process input for the ability.
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
		FGameplayTag InputTag;
};


/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UPuzzleGuyAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()
	

public:

	UPuzzleGuyAbilitySet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:

	// Gameplay abilities to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta = (TitleProperty = Ability))
		TArray<FPuzzleGuyAbilitySet_GameplayAbility> GrantedGameplayAbilities;
};
