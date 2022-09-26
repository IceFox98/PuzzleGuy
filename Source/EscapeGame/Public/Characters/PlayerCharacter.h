// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Misc/Guid.h"
#include "PlayerCharacter.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class ESCAPEGAME_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:

	APlayerCharacter();

private:

protected:
	/** FPS camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UCameraComponent* CameraComp;

	/** Components that manages the interaction with usable actors */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UInteractionComponent* InteractionComponent;

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

	virtual void OnHealthChanged(UHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void Interact();

	void ThrowObject();

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent)
		bool HasKey(FGuid Key);

};
