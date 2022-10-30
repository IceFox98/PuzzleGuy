// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Misc/Guid.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class UInteractionComponent;
class UPuzzleGuyAbilitySystemComponent;
class UPuzzleGuyGameplayAbility;
class UGameplayEffect;
class UPuzzleGuyAttributeSet;

UENUM(BlueprintType)
enum class EPuzzleGuyAbilityInputID : uint8
{
	None,
	Confirm,
	Cancel,
	Jump
};

/**
 *
 */
UCLASS(Blueprintable)
class ESCAPEGAME_API APlayerCharacter : public ACharacterBase, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	APlayerCharacter();

private:

protected:
	/** FPS camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* CameraComp;

	/** Components that manages the interaction with usable actors */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UInteractionComponent* InteractionComponent;

	/** Components that manages the player abilities */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		TObjectPtr<UPuzzleGuyAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
		TObjectPtr<UPuzzleGuyAttributeSet> Attributes;

	/** The location from where the object will be thrown */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Throwing")
		class USceneComponent* ThrowStartingPoint;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UInventoryComponent* InventoryComponent;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Throwing")
		float ThrowForce;

protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;


	/************************
	* Ability System
	*************************/

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	void AddStartupGameplayAbilities();

	// An array that initializes all the attributes set at the beginning of the game
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
		TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
		TArray<TSubclassOf<UPuzzleGuyGameplayAbility>> Abilities;

	UPROPERTY()
		uint8 bAbilitiesInitialized : 1;


	//virtual void OnHealthChanged(UHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) override;

	
	/*
	* Called when health is changed, either from healing or from being damaged
	*/
	UFUNCTION(BlueprintImplementableEvent)
		void OnHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	/** This allows AttributeSet to call the functions above */
	friend UPuzzleGuyAttributeSet;


	/************************
	* Movement
	*************************/

	void MoveForward(float Value);
	void MoveRight(float Value);

	/************************
	* Actions
	*************************/

	void Interact();
	void ThrowObject();

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent)
		bool HasKey(FGuid Key);

};
