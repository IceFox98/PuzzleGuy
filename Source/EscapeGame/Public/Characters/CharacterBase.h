// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class ESCAPEGAME_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

private:

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UHealthComponent* HealthComp;

public:


	/**
	* FUNCTIONS
	*/
private:


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	///**
	// * The event called when the health of this Character changes
	// * @param OwningHealthComp - The Health Component of the Pawn that has changed its health
	// * @param Health - The Current Health of the Pawn
	// * @param HealthDelta - The Health thats has been subtracted
	// */
	//UFUNCTION()
	//	virtual void OnHealthChanged(UHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
