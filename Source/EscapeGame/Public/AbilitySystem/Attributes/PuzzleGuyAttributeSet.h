// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PuzzleGuyAttributeSet.generated.h"

// Users macros from Attributes.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 *
 */
UCLASS()
class ESCAPEGAME_API UPuzzleGuyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPuzzleGuyAttributeSet();

	// Which attributes we need to replicate
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Called before we change an attribute 
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// Called after any GameplayEffect executes
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Attributes")
		FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UPuzzleGuyAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHeath, Category = "Attributes")
		FGameplayAttributeData MaxHeath;
	ATTRIBUTE_ACCESSORS(UPuzzleGuyAttributeSet, MaxHeath);

	// When we adjust a value of a "Max" attribute (for example MaxHealth), it will proportionally
	// adjust the current Health 
	void AdjustAttributeForMaxChange(const FGameplayAttributeData& AffectedAttribute, 
		const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty) const;

	UFUNCTION()
		void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		void OnRep_MaxHeath(const FGameplayAttributeData& OldValue);
};
